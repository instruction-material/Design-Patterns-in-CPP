#include <iostream>
#include <memory>
#include <string>
#include <utility>

struct Checkout {
    std::string label;
};

class Display {
public:
    explicit Display(std::weak_ptr<const Checkout> loan) : loan_(std::move(loan)) {}

    std::string show() const {
        return "(returned)"; // TODO: Read a live loan without storing an owner.
    }

private:
    [[maybe_unused]] std::weak_ptr<const Checkout> loan_;
};

int main() {
    auto loan = std::make_shared<Checkout>(Checkout{"tripod"});
    const Display display(loan);
    std::cout << display.show() << '\n' << loan.use_count() << '\n';
    loan.reset();
    std::cout << display.show() << '\n';
}
