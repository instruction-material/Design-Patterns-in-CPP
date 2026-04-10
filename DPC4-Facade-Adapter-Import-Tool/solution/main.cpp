#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

struct ImportRecord {
	std::string label;
	std::string category;
	int quantity;
};

class ImportSource {
public:
	virtual ~ImportSource() = default;
	virtual std::vector<ImportRecord> import(const std::string& payload) const = 0;
};

class LegacyCsvSource final : public ImportSource {
public:
	std::vector<ImportRecord> import(const std::string& payload) const override {
		std::vector<ImportRecord> records;
		std::istringstream input(payload);
		for (std::string line; std::getline(input, line); ) {
			if (line.empty()) {
				continue;
			}

			std::istringstream row(line);
			std::string name;
			std::string type;
			std::string quantityText;
			std::getline(row, name, ',');
			std::getline(row, type, ',');
			std::getline(row, quantityText, ',');
			records.push_back({name, type, std::stoi(quantityText)});
		}
		return records;
	}
};

class JsonLinesAdapter final : public ImportSource {
public:
	std::vector<ImportRecord> import(const std::string& payload) const override {
		std::vector<ImportRecord> records;
		std::istringstream input(payload);
		for (std::string line; std::getline(input, line); ) {
			if (line.empty()) {
				continue;
			}

			records.push_back({
				extract(line, "\"label\":\"", '"'),
				extract(line, "\"category\":\"", '"'),
				std::stoi(extract(line, "\"quantity\":", '}'))
			});
		}
		return records;
	}

private:
	static std::string extract(
		const std::string& line,
		const std::string& token,
		char terminator
	) {
		const auto start = line.find(token);
		if (start == std::string::npos) {
			return {};
		}
		const auto valueStart = start + token.size();
		const auto valueEnd = line.find(terminator, valueStart);
		return line.substr(valueStart, valueEnd - valueStart);
	}
};

class ImportFacade {
public:
	std::vector<ImportRecord> importRecords(
		const ImportSource& source,
		const std::string& payload
	) const {
		return source.import(payload);
	}

	void printReport(const std::vector<ImportRecord>& records) const {
		std::cout << "Imported " << records.size() << " records\n";
		for (const auto& record : records) {
			std::cout << "  " << record.label << " (" << record.category << ") qty=" << record.quantity << '\n';
		}
	}
};

int main() {
	const std::string csv = "terrain,texture,4\nplayer,sprite,1\nmusic,audio,2\n";
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
