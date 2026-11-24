#include <iostream>
#include <sstream>
#include <string>



std::ostream& globalReceipts() { return std::cout; }

class Exporter {
public:
    // TODO: keep the caller's destination and use it for every receipt.
    explicit Exporter(std::ostream&) {}
    void save(const std::string& name) { globalReceipts() << "saved " << name << '\n'; }
};

bool check(const char* label, const std::string& actual, const std::string& expected) {
    std::cout << label << ": observed [" << actual << "], expected [" << expected << "]\n";
    return actual == expected;
}

int main() {
    std::ostringstream reports, images;
    Exporter report(reports);
    {
        Exporter image(images);
        report.save("notes.txt");
        image.save("map.png");
    }
    report.save("index.csv");
    bool ok = check("report order", reports.str(), "saved notes.txt\nsaved index.csv\n");
    ok &= check("image isolation", images.str(), "saved map.png\n");
    return ok ? 0 : 1;
}
