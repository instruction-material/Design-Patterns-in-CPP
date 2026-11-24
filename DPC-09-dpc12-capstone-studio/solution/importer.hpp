#pragma once

#include <istream>
#include <map>
#include <string>

enum class Format { space, comma };

class Inventory {
public:
    bool import(std::istream& input, Format format);
    std::string report() const;
private:
    std::map<std::string, int> counts_;
};
