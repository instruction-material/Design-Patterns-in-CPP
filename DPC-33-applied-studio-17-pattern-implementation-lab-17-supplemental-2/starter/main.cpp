#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

std::vector<std::int64_t> longGaps(const std::vector<int>& minutes, int threshold) {
    (void)minutes;
    (void)threshold;
    return {}; // TODO: Move gap detection here.
}

int main() {
    const std::vector<int> times{3, 6, 16, 19};
    // Legacy report. Replace the inline scan with a call to longGaps.
    for (std::size_t i = 1; i < times.size(); ++i) {
        const auto gap = std::int64_t{times[i]} - times[i-1];
        if (gap > 5) std::cout << gap << '\n';
    }
}
