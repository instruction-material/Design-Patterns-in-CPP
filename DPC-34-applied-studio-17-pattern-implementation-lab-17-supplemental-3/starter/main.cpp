#include <iostream>
#include <set>
#include <string>

struct Revision {
    std::set<std::string> topics;
};

Revision combined(const Revision& left, const Revision& right) {
    (void)right;
    return left; // TODO: Add the second revision’s topics to a copy.
}

void print(const Revision& revision) {
    for (const auto& label : revision.topics) std::cout << label << '\n';
}

int main() {
    const Revision first{{"draft", "map"}}, second{{"map", "review"}};
    print(combined(first, second));
}
