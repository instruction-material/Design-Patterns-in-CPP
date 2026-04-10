#include <iostream>
#include <memory>
#include <string>
#include <type_traits>
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
	virtual void apply(Document& document) const = 0;
	virtual bool isReplaceCommand() const { return false; }
};

class AppendCommand final : public Command {
public:
	explicit AppendCommand(std::string text) : text_(std::move(text)) {}

	std::string label() const override { return "append"; }
	void apply(Document& document) const override { document.append(text_); }

private:
	std::string text_;
};

class ReplaceCommand final : public Command {
public:
	explicit ReplaceCommand(std::string text) : text_(std::move(text)) {}

	std::string label() const override { return "replace"; }
	void apply(Document& document) const override { document.replaceAll(text_); }
	bool isReplaceCommand() const override { return true; }

private:
	std::string text_;
};

class Mode {
public:
	virtual ~Mode() = default;
	virtual std::string name() const = 0;
	virtual bool allowReplace() const = 0;
};

class DraftMode final : public Mode {
public:
	std::string name() const override { return "draft"; }
	bool allowReplace() const override { return true; }
};

class ReviewMode final : public Mode {
public:
	std::string name() const override { return "review"; }
	bool allowReplace() const override { return false; }
};

class EditorSession {
public:
	EditorSession() : mode_(std::make_unique<DraftMode>()) {}

	void setMode(std::unique_ptr<Mode> nextMode) { mode_ = std::move(nextMode); }

	void execute(const Command& command) {
		if (command.isReplaceCommand() && !mode_->allowReplace()) {
			std::cout << "Mode " << mode_->name() << " rejected command " << command.label() << '\n';
			return;
		}

		history_.push_back(document_.text());
		command.apply(document_);
		std::cout << "Applied " << command.label() << " in mode " << mode_->name() << '\n';
	}

	void undoLast() {
		if (history_.empty()) {
			return;
		}
		document_.replaceAll(history_.back());
		history_.pop_back();
	}

	void print() const {
		std::cout << "Document: " << document_.text() << '\n';
	}

private:
	Document document_;
	std::unique_ptr<Mode> mode_;
	std::vector<std::string> history_;
};

int main() {
	EditorSession session;
	AppendCommand addTitle("Sprint notes");
	ReplaceCommand resetDraft("Release checklist");

	session.execute(addTitle);
	session.print();
	session.setMode(std::make_unique<ReviewMode>());
	session.execute(resetDraft);
	session.undoLast();
	session.print();
	std::cout << "\nTODO: add an explicit command queue and richer editor states.\n";
}
