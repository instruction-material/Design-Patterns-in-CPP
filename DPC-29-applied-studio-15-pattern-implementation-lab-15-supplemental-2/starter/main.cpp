#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

struct Job {
    std::string title;
    int priority;
};

using Compare = std::function<bool(const Job&, const Job&)>;

std::vector<Job> ordered(const std::vector<Job>& jobs, const Compare& compare) {
    (void)compare;
    return jobs; // TODO: Sort a copy using the requested policy.
}

void print(const std::vector<Job>& jobs) {
    for (const auto& job : jobs) std::cout << job.title << ' ';
    std::cout << '\n';
}

int main() {
    const std::vector<Job> jobs{{"Kim", 2}, {"Ada", 1}, {"Bo", 2}};
    print(ordered(jobs, [](const Job& a, const Job& b) { return a.title < b.title; }));
    print(ordered(jobs, [](const Job& a, const Job& b) { return a.priority > b.priority; }));
    print(jobs);
}
