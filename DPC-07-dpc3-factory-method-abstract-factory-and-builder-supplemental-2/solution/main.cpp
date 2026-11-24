#include <iostream>
#include <memory>
#include <string>

class Formatter {
public:
    virtual ~Formatter() = default;
    virtual std::string format(const std::string& city) const = 0;
};

class Domestic final : public Formatter {
public:
    std::string format(const std::string& city) const override { return "DOM " + city; }
};

class International final : public Formatter {
public:
    std::string format(const std::string& city) const override { return "INTL " + city; }
};

class PrintJob {
public:
    virtual ~PrintJob() = default;
    std::string print(const std::string& city) const {
        const auto formatter = makeFormatter();
        return "[" + formatter->format(city) + "]";
    }
protected:
    virtual std::unique_ptr<Formatter> makeFormatter() const = 0;
};

class DomesticJob final : public PrintJob {
    std::unique_ptr<Formatter> makeFormatter() const override {
        return std::make_unique<Domestic>();
    }
};

class InternationalJob final : public PrintJob {
    std::unique_ptr<Formatter> makeFormatter() const override {
        return std::make_unique<International>();
    }
};

bool check(const std::string& label, const std::string& actual, const std::string& expected) {
    std::cout << label << ": observed [" << actual << "], expected [" << expected << "]\n";
    return actual == expected;
}

int main() {
    DomesticJob local;
    InternationalJob abroad;
    const PrintJob& selected = abroad;
    bool ok = check("domestic", local.print("Lima"), "[DOM Lima]");
    ok &= check("international", selected.print("Lima"), "[INTL Lima]");
    ok &= check("multiword city", selected.print("La Paz"), "[INTL La Paz]");
    return ok ? 0 : 1;
}
