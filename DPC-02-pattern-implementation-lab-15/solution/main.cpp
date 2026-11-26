#include <iostream>
#include <string>

struct Exhibit {
    std::string title;
    int room;
};

class Style {
public:
    virtual ~Style() = default;
    virtual std::string format(const Exhibit& exhibit) const = 0;
};

class Brief final : public Style {
public:
    std::string format(const Exhibit& exhibit) const override {
        return exhibit.title;
    }
};

class Detailed final : public Style {
public:
    std::string format(const Exhibit& exhibit) const override {
        return exhibit.title + " (room " + std::to_string(exhibit.room) + ")";
    }
};

class SignPrinter {
public:
    explicit SignPrinter(const Style& style) : style_(&style) {}
    std::string text(const Exhibit& exhibit) const {
        return style_->format(exhibit);
    }
    void use(const Style& style) {
        style_ = &style;
    }

private:
    [[maybe_unused]] const Style* style_;
};

int main() {
    const Brief brief;
    const Detailed detailed;
    const Exhibit maps{"Maps", 4};
    SignPrinter signs(brief), details(detailed);
    std::cout << signs.text(maps) << '\n' << details.text(maps) << '\n';
    signs.use(detailed);
    std::cout << signs.text(maps) << '\n';
    signs.use(brief);
    std::cout << signs.text(maps) << '\n';
}
