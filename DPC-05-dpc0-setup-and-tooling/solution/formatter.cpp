#include "formatter.h"
#include <cctype>
#include <string>

std::string format_title(const std::string& input) {
    std::string result = input;
    bool start_of_word = true;
    for (char& ch : result) {
        const auto byte = static_cast<unsigned char>(ch);
        if (std::isspace(byte)) {
            start_of_word = true;
        } else if (start_of_word) {
            ch = static_cast<char>(std::toupper(byte));
            start_of_word = false;
        }
    }
    return result;
}
