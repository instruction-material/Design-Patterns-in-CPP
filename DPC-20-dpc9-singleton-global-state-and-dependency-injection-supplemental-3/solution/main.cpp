#include <iostream>
#include <sstream>
#include <string>



class Exporter {
public:
    explicit Exporter(std::ostream& receipts) : receipts_(receipts) {}
    void save(const std::string& name) { receipts_ << "saved " << name << '\n'; }
private:
    std::ostream& receipts_;
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
