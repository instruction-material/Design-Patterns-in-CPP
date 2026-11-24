#include <iostream>
#include <optional>
#include <string>
#include <utility>

struct Listing {
    std::string title;
    std::string room;
    int capacity;
};

class ListingBuilder {
public:
    ListingBuilder& title(std::string value) { title_ = std::move(value); return *this; }
    ListingBuilder& room(std::string value) { room_ = std::move(value); return *this; }
    ListingBuilder& capacity(int value) { capacity_ = value; return *this; }

    std::optional<Listing> build() const {
        // TODO: enforce the construction rules and preserve all configured fields.
        return Listing{title_, "online", 1};
    }
private:
    std::string title_;
    std::string room_ = "online";
    int capacity_ = 1;
};

std::string describe(const std::optional<Listing>& listing) {
    if (!listing) return "invalid";
    return listing->title + "/" + listing->room + "/" + std::to_string(listing->capacity);
}

bool check(const std::string& label, const std::string& actual, const std::string& expected) {
    std::cout << label << ": observed [" << actual << "], expected [" << expected << "]\n";
    return actual == expected;
}

int main() {
    ListingBuilder builder;
    bool ok = check("missing title", describe(builder.build()), "invalid");
    const auto first = builder.title("Maps").build();
    ok &= check("defaults", describe(first), "Maps/online/1");
    const auto studio = builder.room("Lab A").capacity(12).build();
    ok &= check("configured", describe(studio), "Maps/Lab A/12");
    ok &= check("original snapshot", describe(first), "Maps/online/1");
    ok &= check("zero capacity", describe(builder.capacity(0).build()), "invalid");
    return ok ? 0 : 1;
}
