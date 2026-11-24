#include "temperature.h"
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    if (argc != 2) return 2;
    const std::string name = argv[1];
    if (name == "even_sum") {
        const auto actual = mean_temperature(10, 14);
        if (actual == 12.0) return 0;
        std::cerr << "Expected [" << 12.0 << "], observed [" << actual << "]\n";
        return 1;
    }
    if (name == "half_degree") {
        const auto actual = mean_temperature(12, 15);
        if (actual == 13.5) return 0;
        std::cerr << "Expected [" << 13.5 << "], observed [" << actual << "]\n";
        return 1;
    }
    if (name == "below_zero") {
        const auto actual = mean_temperature(-4, -1);
        if (actual == -2.5) return 0;
        std::cerr << "Expected [" << -2.5 << "], observed [" << actual << "]\n";
        return 1;
    }
    return 2;
}
