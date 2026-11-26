#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

struct Instrument {
    std::string label;
};

class Bench {
public:
    bool accept(std::unique_ptr<Instrument> tool) {
        if (!tool) return false;
        // TODO: Add the instrument without copying it.
        return false;
    }

    const Instrument* find(std::string_view name) const {
        const auto found = std::ranges::find_if(items_, [name](const auto& item) {
            return item->label == name;
        });
        return found == items_.end() ? nullptr : found->get();
    }

    std::unique_ptr<Instrument> extract(std::string_view name) {
        (void)name;
        return {}; // TODO: Return the owner of the matching instrument.
    }

private:
    std::vector<std::unique_ptr<Instrument>> items_;
};

int main() {
    Bench bench;
    auto lute = std::make_unique<Instrument>(Instrument{"lute"});
    const Instrument* address = lute.get();
    bench.accept(std::move(lute));
    bench.accept(std::make_unique<Instrument>(Instrument{"drum"}));
    const Instrument* stored = bench.find("lute");
    std::cout << std::boolalpha << "Original address: "
              << (stored && stored == address) << '\n';
    const auto returned = bench.extract("lute");
    std::cout << "Returned: " << (returned ? returned->label : "(empty)") << '\n';
    std::cout << "Lute removed: " << (bench.find("lute") == nullptr) << '\n';
    std::cout << "Unknown is empty: " << !bench.extract("missing") << '\n';
    std::cout << "Drum remains: " << (bench.find("drum") != nullptr) << '\n';
}
