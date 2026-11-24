#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

struct Event { std::string topic; std::string detail; };

struct Listener {
    virtual ~Listener() = default;
    virtual void receive(const Event& event) = 0;
};

struct Reporter final : Listener {
    explicit Reporter(std::string name) : name_(std::move(name)) {}
    void receive(const Event& event) override {
        std::cout << name_ << ": " << event.detail << '\n';
    }
  private:
    std::string name_;
};

class MatchFeed {
    struct Slot { std::string topic; std::weak_ptr<Listener> listener; };
    std::vector<Slot> slots_;
  public:
    void subscribe(std::string topic, const std::shared_ptr<Listener>& listener) {
        slots_.push_back({std::move(topic), listener});
    }
    void publish(const Event& event) const {
        const auto subscribers = slots_;
        for (const auto& slot : subscribers) {
            if (!slot.topic.empty() && slot.topic != event.topic) continue;
            if (auto listener = slot.listener.lock()) listener->receive(event);
        }
    }
};

int main() {
    MatchFeed feed;
    auto score = std::make_shared<Reporter>("scoreboard");
    auto ref = std::make_shared<Reporter>("referee");
    auto log = std::make_shared<Reporter>("log");
    feed.subscribe("goal", score);
    feed.subscribe("foul", ref);
    feed.subscribe("", log);
    feed.publish({"goal", "blue scores"});
    feed.publish({"foul", "holding"});
    ref.reset();
    feed.publish({"foul", "offside"});
}
