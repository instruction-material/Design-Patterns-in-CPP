#include <iostream>
#include <string>
#include <vector>

struct Task {
    std::string title;
    int minutes;
};

struct Plan {
    std::vector<std::string> titles;
    int spent = 0;
};

Plan buildPlan(const std::vector<Task>& tasks, int budget) {
    // TODO: Select the tasks within budget without printing in this function.
    (void)tasks;
    (void)budget;
    return {};
}

void print(const Plan& plan) {
    for (const auto& title : plan.titles) std::cout << title << '\n';
    std::cout << "Minutes: " << plan.spent << '\n';
}

int main() {
    const std::vector<Task> tasks{{"Sketch", 15}, {"Assemble", 20}, {"Pack", 10}};
    print(buildPlan(tasks, 35));
}
