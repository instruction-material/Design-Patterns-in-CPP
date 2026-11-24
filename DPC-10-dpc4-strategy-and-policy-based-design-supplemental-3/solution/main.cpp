#include <iostream>
#include <vector>

template<int Limit>
struct AtLeast {
    static bool flags(int value) { return value >= Limit; }
};

template<int Low, int High>
struct OutsideBand {
    static_assert(Low <= High, "The lower limit must not exceed the upper limit");
    static bool flags(int value) { return value < Low || value > High; }
};

template<class Policy>
std::vector<int> flagged(const std::vector<int>& readings) {
    std::vector<int> result;
    for (int value : readings) {
        if (Policy::flags(value)) result.push_back(value);
    }
    return result;
}

void print(const char* label, const std::vector<int>& values) {
    std::cout << label;
    for (int value : values) std::cout << ' ' << value;
    std::cout << '\n';
}

int main() {
    const std::vector<int> readings{9, 10, 20, 30, 31};
    print("hot:", flagged<AtLeast<30>>(readings));
    print("outside:", flagged<OutsideBand<10, 30>>(readings));
}
