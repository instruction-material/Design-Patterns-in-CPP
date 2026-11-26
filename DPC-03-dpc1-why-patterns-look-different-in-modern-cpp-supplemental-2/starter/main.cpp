#include <iostream>
#include <memory>
#include <string>
#include <utility>

struct Draft {
    std::string title;
};

class Inbox {
    std::unique_ptr<Draft> current_;
  public:
    explicit Inbox(std::unique_ptr<Draft> draft) : current_(std::move(draft)) {}

    const Draft* preview() const { return current_.get(); }

    std::unique_ptr<Draft> take() {
        // TODO: transfer the current draft.
        return nullptr;
    }
};

int main() {
    Inbox inbox(std::make_unique<Draft>(Draft{"Sketch"}));
    if (const auto* draft = inbox.preview()) std::cout << "Preview: " << draft->title << '\n';
    auto claimed = inbox.take();
    std::cout << "Claimed: " << (claimed ? claimed->title : "(empty)") << '\n';
    std::cout << "Inbox: " << (inbox.preview() ? "occupied" : "empty") << '\n';
}
