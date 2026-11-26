#include <cstdint>
#include <iostream>

enum class Loan { Ordinary, Oversize };

struct Fees {
    int ordinary = 75;
    int oversize = 200;
};

std::int64_t feeFor(Loan loan, int lateDays, [[maybe_unused]] const Fees& fees) {
    if (lateDays <= 0) return 0;
    if (loan == Loan::Oversize) return std::int64_t{200} * lateDays;
    return std::int64_t{75} * lateDays; // TODO: Apply the supplied fees.
}

int main() {
    const Fees defaults;
    const Fees eventRates{25, 50};
    for (const auto fees : {defaults, eventRates}) {
        std::cout << feeFor(Loan::Ordinary, 2, fees) << ' '
                  << feeFor(Loan::Oversize, 1, fees) << '\n';
    }
}
