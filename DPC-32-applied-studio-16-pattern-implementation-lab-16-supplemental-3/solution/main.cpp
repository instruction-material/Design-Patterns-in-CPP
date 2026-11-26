#include <iostream>
#include <map>
#include <optional>
#include <string>

struct Catalogue {
    std::map<int, std::string> titles;
    int calls = 0;

    std::optional<std::string> find(int id) {
        ++calls;
        auto found = titles.find(id);
        if (found == titles.end()) return {};
        return found->second;
    }
};

class Memo {
public:
    explicit Memo(Catalogue& source) : source_(source) {}

    std::optional<std::string> find(int id) {
        const auto saved = cache_.find(id);
        if (saved != cache_.end()) return saved->second;
        const auto title = source_.find(id);
        cache_.emplace(id, title);
        return title;
    }

    void clear() { cache_.clear(); }

private:
    Catalogue& source_;
    std::map<int, std::optional<std::string>> cache_;
};

int main() {
    Catalogue source{{{7, "Gallery"}}};
    Memo memo(source);
    for (int id : {7, 7, 9, 9}) std::cout << memo.find(id).value_or("(missing)") << '\n';
    std::cout << "Calls: " << source.calls << '\n';
    memo.clear();
    memo.find(7);
    std::cout << "Calls: " << source.calls << '\n';
}
