#include <cassert>
#include <iostream>
#include <set>
#include <utility>

class Registry {
    unsigned next_ = 0;
    std::set<unsigned> live_;
  public:
    Registry() = default;
    Registry(const Registry&) = delete;
    Registry& operator=(const Registry&) = delete;

    unsigned acquire() {
        const auto slot = next_++;
        live_.insert(slot);
        return slot;
    }
    void release(unsigned slot) {
        const auto removed = live_.erase(slot);
        assert(removed == 1);
        (void)removed;
    }
    std::size_t active() const { return live_.size(); }
};

class Lease {
    Registry* registry_;
    unsigned slot_;
  public:
    explicit Lease(Registry& registry) : registry_(&registry), slot_(registry.acquire()) {}
    ~Lease() { reset(); }
    Lease(const Lease&) = delete;
    Lease& operator=(const Lease&) = delete;

    Lease(Lease&& other) noexcept
        : registry_(std::exchange(other.registry_, nullptr)), slot_(other.slot_) {}

    Lease& operator=(Lease&& other) noexcept {
        if (this != &other) {
            reset();
            registry_ = std::exchange(other.registry_, nullptr);
            slot_ = other.slot_;
        }
        return *this;
    }
    bool ownsSlot() const { return registry_ != nullptr; }

  private:
    void reset() noexcept {
        if (registry_) registry_->release(slot_);
        registry_ = nullptr;
    }
};

int main() {
    Registry registry;
    {
        Lease first(registry), second(registry);
        std::cout << registry.active() << '\n';
        second = std::move(first);
        std::cout << registry.active() << " " << std::boolalpha << first.ownsSlot() << '\n';
    }
    std::cout << registry.active() << '\n';
}
