#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

std::vector<std::int64_t> longGaps(const std::vector<int>& minutes, int threshold) {
    std::vector<std::int64_t> gaps;
    for (std::size_t i = 1; i < minutes.size(); ++i) {
        const auto gap = std::int64_t{minutes[i]} - minutes[i-1];
        if (gap > threshold) gaps.push_back(gap);
    }
    return gaps;
}

int main() {
    const std::vector<int> times{3, 6, 16, 19};
    for (const auto gap : longGaps(times, 5)) std::cout << gap << '\n';
}
