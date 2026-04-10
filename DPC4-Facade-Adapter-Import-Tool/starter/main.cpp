#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct LegacyRecord {
	std::string name;
	std::string type;
	int quantity;
};

struct ImportRecord {
	std::string label;
	std::string category;
	int quantity;
};

class LegacyCsvLoader {
public:
	std::vector<LegacyRecord> load(const std::string& csv) const {
		std::vector<LegacyRecord> rows;
		std::istringstream input(csv);
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
			rows.push_back({name, type, std::stoi(quantityText)});
		}
		return rows;
	}
};

class LegacyCsvAdapter {
public:
	explicit LegacyCsvAdapter(LegacyCsvLoader loader) : loader_(std::move(loader)) {}

	std::vector<ImportRecord> import(const std::string& csv) const {
		std::vector<ImportRecord> records;
		for (const auto& row : loader_.load(csv)) {
			records.push_back({row.name, row.type, row.quantity});
		}
		return records;
	}

private:
	LegacyCsvLoader loader_;
};

class ImportFacade {
public:
	explicit ImportFacade(LegacyCsvAdapter csvAdapter) : csvAdapter_(std::move(csvAdapter)) {}

	void printReport(const std::string& csv) const {
		const auto records = csvAdapter_.import(csv);
		std::cout << "Imported " << records.size() << " records\n";
		for (const auto& record : records) {
			std::cout << "  " << record.label << " (" << record.category << ") qty=" << record.quantity << '\n';
		}
	}

private:
	LegacyCsvAdapter csvAdapter_;
};

int main() {
	const std::string csv = "terrain,texture,4\nplayer,sprite,1\nmusic,audio,2\n";
	ImportFacade facade(LegacyCsvAdapter(LegacyCsvLoader{}));
	facade.printReport(csv);
	std::cout << "\nTODO: add a second adapter so the facade can hide both CSV and another external format.\n";
}
