#include "importer.hpp"

#include <charconv>
#include <sstream>
#include <system_error>
#include <utility>

namespace {
constexpr int maxTotal = 1000000;
constexpr int maxDelta = 10000;

bool parseQuantity(const std::string& token, int& result) {
    const char* end = token.data() + token.size();
    const auto parsed = std::from_chars(token.data(), end, result);
    return parsed.ec == std::errc{} && parsed.ptr == end && result > 0 && result <= maxDelta;
}

bool validName(const std::string& name) {
    return !name.empty() && name.find_first_not_of("abcdefghijklmnopqrstuvwxyz0123456789_") == std::string::npos;
}

struct Record {
    std::string name;
    int quantity;
};

bool parseSpace(const std::string& line, std::string& name, std::string& quantity) {
    std::istringstream fields(line);
    std::string extra;
    return (fields >> name >> quantity) && !(fields >> extra);
}

bool parseComma(const std::string& line, std::string& name, std::string& quantity) {
    const auto divider = line.find(',');
    if (divider == std::string::npos || line.find(',', divider + 1) != std::string::npos) return false;
    name = line.substr(0, divider);
    quantity = line.substr(divider + 1);
    return true;
}
using Parser = bool (*)(const std::string&, std::string&, std::string&);

bool readRecord(const std::string& line, Parser parse, Record& result) {
    std::string count;
    return parse(line, result.name, count) && validName(result.name) && parseQuantity(count, result.quantity);
}
} // namespace

bool Inventory::import(std::istream& input, Format format) {
    const Parser parse = format == Format::space ? parseSpace : parseComma;
    auto pending = counts_;
    for (std::string line; std::getline(input, line);) {
        if (line.empty()) continue;
        Record record{};
        if (!readRecord(line, parse, record)) return false;
        int& total = pending[record.name];
        if (total > maxTotal - record.quantity) return false;
        total += record.quantity;
    }
    if (input.bad() || !input.eof()) return false;
    counts_.swap(pending);
    return true;
}

std::string Inventory::report() const {
    std::ostringstream out;
    for (const auto& [name, quantity] : counts_) out << name << '=' << quantity << '\n';
    return out.str();
}
