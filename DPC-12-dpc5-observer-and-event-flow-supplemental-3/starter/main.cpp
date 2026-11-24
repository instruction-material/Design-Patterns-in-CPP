#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

using Callback = std::function<void()>;

class Connection {
    std::shared_ptr<Callback> callback_;
  public:
    explicit Connection(std::shared_ptr<Callback> callback) : callback_(std::move(callback)) {}
    Connection(const Connection&) = delete;
    Connection& operator=(const Connection&) = delete;
    Connection(Connection&&) noexcept = default;
    Connection& operator=(Connection&&) noexcept = default;
    void disconnect() {
        // TODO: release the owned callback.
    }
};

class Clock {
    std::vector<std::weak_ptr<Callback>> callbacks_;
  public:
    Connection subscribe(Callback fn) {
        auto entry = std::make_shared<Callback>(std::move(fn));
        callbacks_.push_back(entry);
        return Connection(std::move(entry));
    }
    std::size_t registeredSlots() const { return callbacks_.size(); }
    void tick() {
        // TODO: remove expired weak references.
        const auto snapshot = callbacks_;
        for (const auto& slot : snapshot) {
            if (const auto active = slot.lock()) (*active)();
        }
    }
};

int main() {
    Clock clock;
    int first = 0, second = 0;
    auto original = clock.subscribe([&] { ++first; });
    auto moved = std::move(original);
    original.disconnect();
    {
        auto other = clock.subscribe([&] { ++second; });
        clock.tick();
        moved.disconnect();
        clock.tick();
    }
    clock.tick();
    std::cout << "first=" << first << " second=" << second
              << " slots=" << clock.registeredSlots() << '\n';
}
