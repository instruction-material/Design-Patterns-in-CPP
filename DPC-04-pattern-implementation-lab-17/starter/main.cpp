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
    (void)rows;
    return {}; // TODO: Count positive quantities by state here.
}

void print(const Summary& report, bool includeRetired = false) {
    std::cout << "ready=" << report.ready << '\n';
    std::cout << "repair=" << report.repair << '\n';
    if (includeRetired) std::cout << "retired=" << report.retired << '\n';
}

int main() {
    const std::vector<Row> initial{{State::Ready, 2}, {State::Repair, 1}, {State::Ready, 3}};
    // Legacy path. Replace the inline count with a call to summarize.
    Summary counts;
    for (const auto& row : initial) {
        if (row.quantity <= 0) continue;
        if (row.state == State::Ready) counts.ready += row.quantity;
        if (row.state == State::Repair) counts.repair += row.quantity;
    }
    print(counts);
    auto extra = initial;
    extra.push_back({State::Retired, 3});
    print(summarize(extra), true);
}
