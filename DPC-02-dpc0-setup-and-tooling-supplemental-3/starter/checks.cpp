#include "length.h"
#include <iostream>

int main() {
    if (millimetres(0) == 0 && millimetres(3) == 30) return 0;
    std::cerr << "Expected 0 and 30 millimetres.\n";
    return 1;
}
