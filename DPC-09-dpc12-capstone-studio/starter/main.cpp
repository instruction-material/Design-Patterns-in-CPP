#include "importer.hpp"

#include <iostream>
#include <string_view>

int main(int argc, char* argv[]) {
    if (argc != 2 || (std::string_view(argv[1]) != "space" && std::string_view(argv[1]) != "comma")) {
        std::cerr << "Usage: asset_import space|comma\n";
        return 2;
    }
    Inventory inventory;
    const Format format = std::string_view(argv[1]) == "space" ? Format::space : Format::comma;
    if (!inventory.import(std::cin, format)) {
        std::cerr << "Invalid batch\n";
        return 1;
    }
    std::cout << inventory.report();
}
