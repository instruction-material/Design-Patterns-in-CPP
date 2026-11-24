#include "importer.hpp"

#include <iostream>
#include <sstream>
#include <string>

bool apply(Inventory& inventory, Format format, const std::string& text) {
    std::istringstream input(text);
    return inventory.import(input, format);
}

bool run(const std::string& name) {
    Inventory data;
    constexpr auto space = Format::space;
    constexpr auto comma = Format::comma;
    if (name == "standard") {
        return apply(data, space, "tile 2\nhero 1\ntile 3\n") &&
               data.report() == "hero=1\ntile=5\n";
    }
    if (name == "malformed") {
        if (!apply(data, space, "hero 2\n")) return false;
        for (const std::string invalid : {"x 0", "Hero 2", "tile 2 extra", "b 3x", "a 10001"}) {
            if (apply(data, space, "tile 4\n" + invalid) || data.report() != "hero=2\n") return false;
        }
        return true;
    }
    if (name == "limit") {
        std::string records;
        for (int i = 0; i < 100; ++i) records += "tile 10000\n";
        return apply(data, space, records) && !apply(data, space, "tile 1") &&
               data.report() == "tile=1000000\n";
    }
    if (name == "isolation") {
        Inventory second;
        return apply(data, space, "day 1") && apply(second, space, "") &&
               second.report().empty() && data.report() == "day=1\n";
    }
    if (name == "comma") {
        return apply(data, comma, "tile,2\nhero,1\ntile,3") &&
               data.report() == "hero=1\ntile=5\n";
    }
    if (name == "mixed") {
        return apply(data, space, "tile 1") && apply(data, comma, "tile,2") &&
               !apply(data, comma, "hero,4\ntile,2,3") && data.report() == "tile=3\n";
    }
    return false;
}
int main(int argc, char* argv[]) {
    if (argc != 2 || !run(argv[1])) {
        std::cerr << "Failed: " << (argc == 2 ? argv[1] : "missing test") << '\n';
        return 1;
    }
}
