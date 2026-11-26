#include <iomanip>
#include <iostream>
#include <string>

struct Cut {
    std::string label;
    double centimetres;
};

struct InchCut {
    std::string label;
    double inches;
};

Cut normalize(const InchCut& input) {
    return {input.label, input.inches}; // TODO: Convert the value.
}

void print(const Cut& item) {
    std::cout << item.label << ": " << std::fixed << std::setprecision(2)
              << item.centimetres << " cm\n";
}

int main() {
    print({"Shelf", 25.4});
    print(normalize({"Door", 10.0}));
}
