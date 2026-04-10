#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

struct Task {
	std::string channel;
	std::string body;
	bool urgent;
};

class DeliveryStrategy {
public:
	virtual ~DeliveryStrategy() = default;
	virtual void send(const Task& task) const = 0;
};

class EmailDelivery final : public DeliveryStrategy {
public:
	void send(const Task& task) const override {
		std::cout << "[email] " << task.body << '\n';
	}
};

class ChatDelivery final : public DeliveryStrategy {
public:
	void send(const Task& task) const override {
		std::cout << "[chat] " << task.body << '\n';
	}
};

class PriorityPolicy {
public:
	std::string describe(const Task& task) const {
		return task.urgent ? "[priority] escalate immediately" : "[priority] standard handling";
	}
};

class DeliveryFactory {
public:
	static std::unique_ptr<DeliveryStrategy> create(const std::string& channel) {
		if (channel == "email") {
			return std::make_unique<EmailDelivery>();
		}
		return std::make_unique<ChatDelivery>();
	}
};

class DispatchFacade {
public:
	void dispatch(const Task& task) const {
		auto delivery = DeliveryFactory::create(task.channel);
		delivery->send(task);
		std::cout << policy_.describe(task) << '\n';
	}

private:
	PriorityPolicy policy_;
};

int main() {
	const std::vector<Task> tasks = {
		{"email", "Nightly report is ready", false},
		{"chat", "Deploy rollback requested", true}
	};

	DispatchFacade facade;
	for (const auto& task : tasks) {
		facade.dispatch(task);
	}
}
