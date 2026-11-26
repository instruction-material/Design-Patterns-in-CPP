#include <iostream>
#include <set>
#include <string>

struct Revision {
    std::set<std::string> topics;
};

Revision combined(const Revision& left, const Revision& right) {
    Revision result = left;
    result.topics.insert(right.topics.begin(), right.topics.end());
    return result;
}

void print(const Revision& revision) {
    for (const auto& label : revision.topics) std::cout << label << '\n';
}

int main() {
    const Revision first{{"draft", "map"}}, second{{"map", "review"}};
    print(combined(first, second));
}
