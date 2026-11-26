#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

struct Board {
    std::vector<std::string> labels;
};

class FrameBatch {
public:
    explicit FrameBatch(Board& board) : board_(board) {}
    FrameBatch(const FrameBatch&) = delete;
    FrameBatch& operator=(const FrameBatch&) = delete;

    bool append(std::string label) {
        if (finished_) return false;
        pending_.push_back(std::move(label));
        return true;
    }

    bool commit() noexcept {
        if (finished_ || pending_.empty() ||
            std::ranges::any_of(pending_, [](const std::string& label) { return label.empty(); })) {
            return false;
        }
        board_.labels.swap(pending_);
        finished_ = true;
        return true;
    }

private:
    [[maybe_unused]] Board& board_;
    std::vector<std::string> pending_;
    bool finished_ = false;
};

int main() {
    Board board{{"Original"}};
    FrameBatch invalid(board);
    invalid.append("Map");
    invalid.append("");
    std::cout << std::boolalpha << invalid.commit() << ' ' << board.labels.front() << '\n';
    FrameBatch good(board);
    good.append("Map");
    good.append("Key");
    std::cout << good.commit();
    for (const auto& label : board.labels) std::cout << ' ' << label;
    std::cout << '\n' << good.commit() << '\n';
}
