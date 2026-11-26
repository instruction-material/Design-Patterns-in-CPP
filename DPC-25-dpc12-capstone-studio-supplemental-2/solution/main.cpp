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
    Plan plan;
    if (budget <= 0) return plan;
    for (const auto& task : tasks) {
        if (task.minutes <= 0) continue;
        if (task.minutes > budget - plan.spent) break;
        plan.titles.push_back(task.title);
        plan.spent += task.minutes;
    }
    return plan;
}

void print(const Plan& plan) {
    for (const auto& title : plan.titles) std::cout << title << '\n';
    std::cout << "Minutes: " << plan.spent << '\n';
}

int main() {
    const std::vector<Task> tasks{{"Sketch", 15}, {"Assemble", 20}, {"Pack", 10}};
    print(buildPlan(tasks, 35));
}
