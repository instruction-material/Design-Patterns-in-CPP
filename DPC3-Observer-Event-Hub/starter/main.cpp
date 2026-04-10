#include <iostream>
#include <memory>
#include <string>
#include <vector>

struct Event {
	std::string topic;
	int severity;
	std::string message;
};

class Listener {
public:
	virtual ~Listener() = default;
	virtual void onEvent(const Event& event) = 0;
};

class ConsoleListener final : public Listener {
public:
	void onEvent(const Event& event) override {
		std::cout << "[console] " << event.topic << " severity=" << event.severity << " " << event.message << '\n';
	}
};

class EscalationListener final : public Listener {
public:
	void onEvent(const Event& event) override {
		if (event.severity >= 4) {
			std::cout << "[escalation] page the operator for " << event.topic << '\n';
		}
	}
};

class EventHub {
public:
	void subscribe(const std::shared_ptr<Listener>& listener) {
		listeners_.push_back(listener);
	}

	void publish(const Event& event) {
		for (const auto& slot : listeners_) {
			if (const auto listener = slot.lock()) {
				listener->onEvent(event);
			}
		}
	}

private:
	std::vector<std::weak_ptr<Listener>> listeners_;
};

int main() {
	EventHub hub;
	auto console = std::make_shared<ConsoleListener>();
	auto escalation = std::make_shared<EscalationListener>();

	hub.subscribe(console);
	hub.subscribe(escalation);
	hub.publish({"build.complete", 2, "nightly build completed"});
	hub.publish({"api.latency", 5, "latency crossed the threshold"});
	std::cout << "\nTODO: clean up expired listeners and add a pull-style summary listener.\n";
}
