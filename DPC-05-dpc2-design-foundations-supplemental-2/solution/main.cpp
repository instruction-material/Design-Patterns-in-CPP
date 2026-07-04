#include <cctype>
#include <iostream>
#include <memory>
#include <string>

/*****************
*   CONSTANTS   *
*****************/

const std::string SAMPLE_TEXT = "design patterns";


/*************
*   TYPES   *
*************/

// Define the formatting strategy interface
class Formatter {
public:
	virtual ~Formatter() = default;

	/**
	 * @brief Format the provided input string
	 *
	 * @param input Text to format
	 *
	 * @return Formatted text
	 */
	virtual std::string format(const std::string& input) const = 0;
};

// Format text by capitalizing the first letter of each word
class TitleFormatter : public Formatter {
public:
	/**
	 * @brief Convert input text to title case
	 *
	 * @param input Text to format
	 *
	 * @return Title-cased text
	 */
	std::string format(const std::string& input) const override {
		std::string output = input;
		bool should_uppercase_next_letter = true;

		// Visit each character so word starts can be capitalized in place
		for (char& character : output) {
			// Spaces make the next non-space character start a new word
			if (std::isspace(static_cast<unsigned char>(character))) {
				should_uppercase_next_letter = true;
				continue;
			}

			// Capitalize the first character after a word boundary
			if (should_uppercase_next_letter) {
				character = static_cast<char>(
					std::toupper(static_cast<unsigned char>(character))
				);
				should_uppercase_next_letter = false;
			}
		}

		return output;
	}
};


/*****************
*   FUNCTIONS   *
*****************/

/**
 * @brief Print a title-formatted sample phrase
 *
 * @return Program exit status
 */
int main() {
	std::unique_ptr<Formatter> formatter = std::make_unique<TitleFormatter>();
	std::cout << formatter->format(SAMPLE_TEXT) << "\n";
	return 0;
}
