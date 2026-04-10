#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class Document {
public:
	void append(const std::string& text) { content_ += text; }
	void replaceAll(const std::string& text) { content_ = text; }
	const std::string& text() const { return content_; }

private:
	std::string content_;
};

class Command {
public:
	virtual ~Command() = default;
	virtual std::string label() const = 0;
	virtual bool allowedInReviewMode() const = 0;
	virtual void apply(Document& document) = 0;
	virtual void undo(Document& document) = 0;
};

class AppendCommand final : public Command {
public:
	explicit AppendCommand(std::string text) : text_(std::move(text)) {}

	std::string label() const override { return "append"; }
	bool allowedInReviewMode() const override { return true; }

	void apply(Document& document) override {
		before_ = document.text();
		document.append(text_);
	}

	void undo(Document& document) override {
		document.replaceAll(before_);
	}

private:
	std::string text_;
	std::string before_;
};

class ReplaceCommand final : public Command {
public:
	explicit ReplaceCommand(std::string text) : text_(std::move(text)) {}

	std::string label() const override { return "replace"; }
	bool allowedInReviewMode() const override { return false; }

	void apply(Document& document) override {
		before_ = document.text();
		document.replaceAll(text_);
	}

	void undo(Document& document) override {
		document.replaceAll(before_);
	}

private:
	std::string text_;
	std::string before_;
};

class Mode {
public:
	virtual ~Mode() = default;
	virtual std::string name() const = 0;
	virtual bool canRun(const Command& command) const = 0;
};

class DraftMode final : public Mode {
public:
	std::string name() const override { return "draft"; }
	bool canRun(const Command&) const override { return true; }
};

class ReviewMode final : public Mode {
public:
	std::string name() const override { return "review"; }
	bool canRun(const Command& command) const override {
		return command.allowedInReviewMode();
	}
};

class EditorSession {
public:
	EditorSession() : mode_(std::make_unique<DraftMode>()) {}

	void setMode(std::unique_ptr<Mode> nextMode) { mode_ = std::move(nextMode); }

	void enqueue(std::unique_ptr<Command> command) {
		queue_.push_back(std::move(command));
	}

	void runQueue() {
		for (auto& command : queue_) {
			if (!mode_->canRun(*command)) {
				std::cout << "Mode " << mode_->name() << " rejected " << command->label() << '\n';
				continue;
			}

			command->apply(document_);
			history_.push_back(std::move(command));
		}
		queue_.clear();
	}

	void undoLast() {
		if (history_.empty()) {
			return;
		}

		history_.back()->undo(document_);
		history_.pop_back();
	}

	void print() const {
		std::cout << "Mode=" << mode_->name() << " document=" << document_.text() << '\n';
	}

private:
	Document document_;
	std::unique_ptr<Mode> mode_;
	std::vector<std::unique_ptr<Command>> queue_;
	std::vector<std::unique_ptr<Command>> history_;
};

int main() {
	EditorSession session;
	session.enqueue(std::make_unique<AppendCommand>("Sprint notes"));
	session.enqueue(std::make_unique<AppendCommand>(" + blockers"));
	session.runQueue();
	session.print();

	session.setMode(std::make_unique<ReviewMode>());
	session.enqueue(std::make_unique<ReplaceCommand>("Release checklist"));
	session.enqueue(std::make_unique<AppendCommand>(" [approved]"));
	session.runQueue();
	session.print();
	session.undoLast();
	session.print();
}
