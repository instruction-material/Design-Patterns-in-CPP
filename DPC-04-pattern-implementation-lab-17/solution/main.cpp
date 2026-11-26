#include <cstdint>
#include <iostream>
#include <vector>

enum class State { Ready, Repair, Retired };

struct Row {
    State state;
    int quantity;
};

struct Summary {
    std::int64_t ready = 0;
    std::int64_t repair = 0;
    std::int64_t retired = 0;
};

Summary summarize(const std::vector<Row>& rows) {
    Summary report;
    for (const auto& row : rows) {
        if (row.quantity <= 0) continue;
        switch (row.state) {
        case State::Ready: report.ready += row.quantity; break;
        case State::Repair: report.repair += row.quantity; break;
        case State::Retired: report.retired += row.quantity; break;
        }
    }
    return report;
}

void print(const Summary& report, bool includeRetired = false) {
    std::cout << "ready=" << report.ready << '\n';
    std::cout << "repair=" << report.repair << '\n';
    if (includeRetired) std::cout << "retired=" << report.retired << '\n';
}

int main() {
    const std::vector<Row> initial{{State::Ready, 2}, {State::Repair, 1}, {State::Ready, 3}};
    print(summarize(initial));
    auto extra = initial;
    extra.push_back({State::Retired, 3});
    print(summarize(extra), true);
}
