#include <json-c/json_object.h>
#include <json-c/json_tokener.h>
#include <limits>
#include <memory>
#include <charconv>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

/****************
*   SOLUTION   *
****************/

struct ImportRecord {
    std::string label;
    std::string category;
    int quantity;
};

class ImportSource {
  public:
    virtual ~ImportSource() = default;
    virtual std::vector<ImportRecord>
    import(const std::string& payload) const = 0;
};

class LegacyCsvSource final : public ImportSource {
  public:
    std::vector<ImportRecord>
    import(const std::string& payload) const override {
        std::vector<ImportRecord> records;
        std::istringstream input(payload);
        for (std::string line; std::getline(input, line);) {
            if (line.empty()) {
                continue;
            }

            if (line.back() == '\r') line.pop_back();
            if (line.empty()) continue;
            std::istringstream row(line);
            std::string name, type, quantityText;
            if (!std::getline(row, name, ',') || name.empty() ||
                !std::getline(row, type, ',') || type.empty() ||
                !std::getline(row, quantityText)) {
                throw std::invalid_argument("Expected label,category,quantity");
            }
            int quantity = 0;
            const char* end = quantityText.data() + quantityText.size();
            const auto parsed = std::from_chars(quantityText.data(), end, quantity);
            if (parsed.ec != std::errc{} || parsed.ptr != end || quantity < 0) {
                throw std::invalid_argument("Expected a nonnegative integer quantity");
            }
            records.push_back({name, type, quantity});
        }
        return records;
    }
};

class JsonLinesAdapter final : public ImportSource {
  public:
    std::vector<ImportRecord>
    import(const std::string& payload) const override {
        std::vector<ImportRecord> records;
        std::istringstream input(payload);
        for (std::string line; std::getline(input, line);) {
            if (line.empty()) {
                continue;
            }

            if (line.find_first_not_of(" \t\r") != std::string::npos) {
                records.push_back(parseRecord(line));
            }
        }
        return records;
    }

  private:
    static json_object* field(json_object* object, const char* name, json_type type) {
        json_object* value = nullptr;
        if (!json_object_object_get_ex(object, name, &value) ||
            !json_object_is_type(value, type)) {
            throw std::invalid_argument(std::string("Invalid or missing field: ") + name);
        }
        return value;
    }

    static std::string textField(json_object* object, const char* name) {
        auto* value = field(object, name, json_type_string);
        const auto size = json_object_get_string_len(value);
        if (size == 0) throw std::invalid_argument(std::string("Empty field: ") + name);
        return {json_object_get_string(value), static_cast<std::size_t>(size)};
    }

    static ImportRecord parseRecord(const std::string& line) {
        using Parser = std::unique_ptr<json_tokener, decltype(&json_tokener_free)>;
        using Object = std::unique_ptr<json_object, decltype(&json_object_put)>;
        Parser parser(json_tokener_new(), json_tokener_free);
        if (!parser) throw std::bad_alloc();
        if (line.size() >= static_cast<std::size_t>(std::numeric_limits<int>::max())) {
            throw std::invalid_argument("Record too long");
        }
        json_tokener_set_flags(parser.get(), JSON_TOKENER_STRICT | JSON_TOKENER_VALIDATE_UTF8);
        Object object(json_tokener_parse_ex(parser.get(), line.data(),
                                            static_cast<int>(line.size())), json_object_put);
        if (json_tokener_get_error(parser.get()) != json_tokener_success ||
            json_tokener_get_parse_end(parser.get()) != line.size() ||
            !json_object_is_type(object.get(), json_type_object)) {
            throw std::invalid_argument("Expected one JSON object per line");
        }
        const auto quantity = json_object_get_int64(field(object.get(), "quantity", json_type_int));
        if (quantity < 0 || quantity > std::numeric_limits<int>::max()) {
            throw std::invalid_argument("Quantity is outside the supported range");
        }
        return {textField(object.get(), "label"), textField(object.get(), "category"),
                static_cast<int>(quantity)};
    }
};

class ImportFacade {
  public:
    std::vector<ImportRecord> importRecords(const ImportSource& source,
                                            const std::string& payload) const {
        return source.import(payload);
    }

    void printReport(const std::vector<ImportRecord>& records) const {
        std::cout << "Imported " << records.size() << " records\n";
        for (const auto& record : records) {
            std::cout << "  " << record.label << " (" << record.category
                      << ") qty=" << record.quantity << '\n';
        }
    }
};

int main() {
    const std::string csv =
        "terrain,texture,4\nplayer,sprite,1\nmusic,audio,2\n";
    const std::string jsonLines =
        "{\"label\":\"effects\",\"category\":\"shader\",\"quantity\":3}\n"
        "{\"label\":\"dialog\",\"category\":\"audio\",\"quantity\":1}\n";

    ImportFacade facade;
    LegacyCsvSource csvSource;
    JsonLinesAdapter jsonSource;

    const auto csvRecords = facade.importRecords(csvSource, csv);
    const auto jsonRecords = facade.importRecords(jsonSource, jsonLines);
    facade.printReport(csvRecords);
    facade.printReport(jsonRecords);
}
