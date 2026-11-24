#include <iostream>

class Rate {
public:
    virtual ~Rate() = default;
    virtual int cents(int parcels) const { return 100 * parcels; }
};

class Express final : public Rate {
public:
    int cents(int parcels) const override { return parcels > 0 ? 200 * parcels + 75 : 0; }
};

int quote(Rate selected, int parcels) {
    // TODO: use the caller's selected policy without slicing it.
    return selected.cents(parcels);
}

bool check(const char* label, int actual, int expected) {
    std::cout << label << ": observed " << actual << ", expected " << expected << '\n';
    return actual == expected;
}
int main() {
    Rate standard;
    Express express;
    const Rate& selected = express;
    bool ok = check("standard two", quote(standard, 2), 200);
    ok &= check("express two", quote(selected, 2), 475);
    ok &= check("express one", quote(selected, 1), 275);
    ok &= check("empty shipment", quote(selected, 0), 0);
    return ok ? 0 : 1;
}
