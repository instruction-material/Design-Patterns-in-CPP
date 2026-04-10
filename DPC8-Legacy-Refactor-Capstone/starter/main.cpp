#include <iostream>
#include <string>
#include <vector>

struct Task {
	std::string channel;
	std::string body;
	bool urgent;
};

class LegacyNotifier {
public:
	virtual ~LegacyNotifier() = default;
	virtual void send(const Task& task) = 0;
};

class EmailNotifier final : public LegacyNotifier {
public:
	void send(const Task& task) override {
		std::cout << "[email] " << task.body << '\n';
	}
};

class ChatNotifier final : public LegacyNotifier {
public:
	void send(const Task& task) override {
		std::cout << "[chat] " << task.body << '\n';
	}
};

LegacyNotifier* makeNotifier(const std::string& channel) {
	if (channel == "email") {
		return new EmailNotifier();
	}
	return new ChatNotifier();
}

int main() {
	const std::vector<Task> tasks = {
		{"email", "Nightly report is ready", false},
		{"chat", "Deploy rollback requested", true}
	};

	for (const auto& task : tasks) {
		LegacyNotifier* notifier = makeNotifier(task.channel);
		notifier->send(task);
		if (task.urgent) {
			std::cout << "[manual-step] escalate the task\n";
		}
		delete notifier;
	}

	std::cout << "\nTODO: replace raw ownership and switch-style construction with a small dispatch facade.\n";
}
