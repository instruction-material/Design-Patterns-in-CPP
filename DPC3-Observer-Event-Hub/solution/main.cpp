#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
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

class SummaryListener final : public Listener {
public:
	void onEvent(const Event& event) override {
		lastTopics_.push_back(event.topic);
		if (lastTopics_.size() > 3) {
			lastTopics_.erase(lastTopics_.begin());
		}
	}

	void printSummary() const {
		std::cout << "[summary]";
		for (const auto& topic : lastTopics_) {
			std::cout << ' ' << topic;
		}
		std::cout << '\n';
	}

private:
	std::vector<std::string> lastTopics_;
};

class EventHub {
public:
	void subscribe(const std::shared_ptr<Listener>& listener) {
		listeners_.push_back(listener);
	}

	void publish(const Event& event) {
		cleanupExpired();
		for (const auto& slot : listeners_) {
			if (const auto listener = slot.lock()) {
				listener->onEvent(event);
			}
		}
	}

private:
	void cleanupExpired() {
		listeners_.erase(
			std::remove_if(
				listeners_.begin(),
				listeners_.end(),
				[](const std::weak_ptr<Listener>& slot) { return slot.expired(); }
			),
			listeners_.end()
		);
	}

	std::vector<std::weak_ptr<Listener>> listeners_;
};

int main() {
	EventHub hub;
	auto console = std::make_shared<ConsoleListener>();
	auto escalation = std::make_shared<EscalationListener>();
	auto summary = std::make_shared<SummaryListener>();

	hub.subscribe(console);
	hub.subscribe(escalation);
	hub.subscribe(summary);
	hub.publish({"build.complete", 2, "nightly build completed"});
	hub.publish({"cache.miss", 3, "cache miss rate increased"});
	hub.publish({"api.latency", 5, "latency crossed the threshold"});
	summary->printSummary();

	console.reset();
	hub.publish({"deploy.finish", 1, "deployment wrapped cleanly"});
	summary->printSummary();
}
