#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class SceneNode {
public:
	virtual ~SceneNode() = default;
	virtual void render(std::ostream& out, int depth) const = 0;
	virtual void collectLabels(std::vector<std::string>& labels) const = 0;
};

class Sprite final : public SceneNode {
public:
	explicit Sprite(std::string label) : label_(std::move(label)) {}

	void render(std::ostream& out, int depth) const override {
		out << std::string(static_cast<std::size_t>(depth) * 2, ' ') << "sprite:" << label_ << '\n';
	}

	void collectLabels(std::vector<std::string>& labels) const override {
		labels.push_back(label_);
	}

private:
	std::string label_;
};

class Group final : public SceneNode {
public:
	explicit Group(std::string label) : label_(std::move(label)) {}

	void add(std::unique_ptr<SceneNode> child) {
		children_.push_back(std::move(child));
	}

	void render(std::ostream& out, int depth) const override {
		out << std::string(static_cast<std::size_t>(depth) * 2, ' ') << "group:" << label_ << '\n';
		for (const auto& child : children_) {
			child->render(out, depth + 1);
		}
	}

	void collectLabels(std::vector<std::string>& labels) const override {
		labels.push_back(label_);
		for (const auto& child : children_) {
			child->collectLabels(labels);
		}
	}

private:
	std::string label_;
	std::vector<std::unique_ptr<SceneNode>> children_;
};

int main() {
	auto root = std::make_unique<Group>("scene");
	auto hud = std::make_unique<Group>("hud");
	hud->add(std::make_unique<Sprite>("health-bar"));
	hud->add(std::make_unique<Sprite>("map-icon"));
	root->add(std::move(hud));
	root->add(std::make_unique<Sprite>("player"));

	root->render(std::cout, 0);

	std::vector<std::string> labels;
	root->collectLabels(labels);
	std::cout << "\nCollected labels:";
	for (const auto& label : labels) {
		std::cout << ' ' << label;
	}
	std::cout << "\n\nTODO: add a traversal helper so callers do not need to understand the tree shape.\n";
}
