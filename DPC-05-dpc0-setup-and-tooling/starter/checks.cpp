#include "formatter.h"
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    if (argc != 2) return 2;
    const std::string name = argv[1];
    if (name == "empty") {
        const auto actual = format_title("");
        if (actual == "") return 0;
        std::cerr << "Expected [" << "" << "], observed [" << actual << "]\n";
        return 1;
    }
    if (name == "ordinary") {
        const auto actual = format_title("design patterns");
        if (actual == "Design Patterns") return 0;
        std::cerr << "Expected [" << "Design Patterns" << "], observed [" << actual << "]\n";
        return 1;
    }
    if (name == "spacing") {
        const auto actual = format_title("  red\tfox  ");
        if (actual == "  Red\tFox  ") return 0;
        std::cerr << "Expected [" << "  Red\tFox  " << "], observed [" << actual << "]\n";
        return 1;
    }
    return 2;
}
