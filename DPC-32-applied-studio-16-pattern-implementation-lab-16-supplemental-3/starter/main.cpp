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
		// TODO: return a transformed representation.
		return input;
	}
};

int main() {
	std::unique_ptr<Formatter> formatter = std::make_unique<TitleFormatter>();
	std::cout << formatter->format("design patterns") << "\n";
}
