#include <cctype>
#include <iostream>
#include <memory>
#include <string>

class Formatter {
public:
	virtual ~Formatter() = default;
	virtual std::string format(const std::string& input) const = 0;
};

class TitleFormatter : public Formatter {
public:
	std::string format(const std::string& input) const override {
		std::string output = input;
		bool makeUpper = true;
		for (char& ch : output) {
			if (std::isspace(static_cast<unsigned char>(ch))) {
				makeUpper = true;
				continue;
			}
			if (makeUpper) {
				ch = static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
				makeUpper = false;
			}
		}
		return output;
	}
};

int main() {
	std::unique_ptr<Formatter> formatter = std::make_unique<TitleFormatter>();
	std::cout << formatter->format("design patterns") << "\n";
}
