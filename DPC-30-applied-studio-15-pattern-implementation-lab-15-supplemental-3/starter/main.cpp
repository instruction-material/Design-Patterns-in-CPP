#include <cstdint>
#include <functional>
#include <iostream>
#include <utility>

using Rule = std::function<int(int)>;

class Session {
public:
    explicit Session(Rule rule) : rule_(std::move(rule)) {}

    void use(Rule rule) { rule_ = std::move(rule); }

    std::int64_t measure(int value) {
        (void)value;
        return total_; // TODO: Apply the current rule and record its result.
    }

private:
    Rule rule_;
    std::int64_t total_ = 0;
};

int main() {
    Session session([](int value) { return value; });
    std::cout << session.measure(3) << '\n';
    int offset = 2;
    session.use([offset](int value) { return value + offset; });
    offset = 9;
    std::cout << session.measure(3) << '\n';
    session.use([](int value) { return value; });
    std::cout << session.measure(1) << '\n';
}
