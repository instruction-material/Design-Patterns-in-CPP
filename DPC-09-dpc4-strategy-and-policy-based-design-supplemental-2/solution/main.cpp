#include <iostream>
#include <string>
#include <vector>

struct Job {
    std::string name;
    int minutes;
};

using Jobs = std::vector<Job>;

class SchedulingRule {
  public:
    virtual ~SchedulingRule() = default;
    // Called only when at least one job is pending.
    virtual std::size_t next(const Jobs& pending) const = 0;
};

class ArrivalOrder final : public SchedulingRule {
  public:
    std::size_t next(const Jobs&) const override { return 0; }
};

class ShortestJob final : public SchedulingRule {
  public:
    std::size_t next(const Jobs& pending) const override {
        std::size_t best = 0;
        for (std::size_t i = 1; i < pending.size(); ++i) {
            if (pending[i].minutes < pending[best].minutes) best = i;
        }
        return best;
    }
};

std::vector<std::string> schedule(Jobs pending, const SchedulingRule& rule) {
    std::vector<std::string> completed;
    while (!pending.empty()) {
        const auto index = rule.next(pending);
        completed.push_back(pending.at(index).name);
        pending.erase(pending.begin() + static_cast<Jobs::difference_type>(index));
    }
    return completed;
}

int main(int argc, char** argv) {
    ArrivalOrder arrival;
    ShortestJob shortest;
    const SchedulingRule* rule = &arrival;
    if (argc == 2 && std::string(argv[1]) == "shortest") rule = &shortest;
    else if (argc != 1) { std::cerr << "Usage: practice [shortest]\n"; return 2; }
    Jobs jobs{{"poster", 8}, {"card", 2}, {"label", 2}, {"map", 5}};
    for (const auto& name : schedule(jobs, *rule)) std::cout << name << '\n';
}
