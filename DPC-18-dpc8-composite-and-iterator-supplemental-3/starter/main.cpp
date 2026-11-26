#include <deque>
#include <iostream>
#include <string>
#include <vector>

struct Node {
    std::string title;
    std::vector<Node> children;
};

class OutlineCursor {
    std::deque<const Node*> pending_;
  public:
    explicit OutlineCursor(const Node& root) : pending_{&root} {}
    const Node* next() {
        if (pending_.empty()) return nullptr;
        const Node* current = pending_.front();
        pending_.pop_front();
        // TODO: enqueue the current node’s children.
        return current;
    }
};

int main() {
    const Node outline{"Course", {
        {"Week 1", {{"Arrays", {}}, {"Loops", {}}}},
        {"Week 2", {{"Grid", {}}}}
    }};
    OutlineCursor cursor(outline);
    while (const Node* node = cursor.next()) std::cout << node->title << '\n';
}
