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
} // namespace

bool Inventory::import(std::istream& input, Format format) {
    // TODO: protect the space format, extract record parsing, then add the comma format.
    if (format != Format::space) return false;
    auto pending = counts_;
    for (std::string line; std::getline(input, line);) {
        if (line.empty()) continue;
        std::istringstream fields(line);
        std::string name, quantity, extra;
        if (!(fields >> name >> quantity) || fields >> extra) return false;
        int amount = 0;
        if (!validName(name) || !parseQuantity(quantity, amount)) return false;
        if (pending[name] > maxTotal - amount) return false;
        pending[name] += amount;
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
