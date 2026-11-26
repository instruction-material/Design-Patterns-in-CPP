#include <cstdint>
#include <iostream>

enum class Loan { Ordinary, Oversize };

struct Fees {
    int ordinary = 75;
    int oversize = 200;
};

std::int64_t feeFor(Loan loan, int lateDays, [[maybe_unused]] const Fees& fees) {
    if (lateDays <= 0) return 0;
    const int rate = loan == Loan::Ordinary ? fees.ordinary : fees.oversize;
    return std::int64_t{rate} * lateDays;
}

int main() {
    const Fees defaults;
    const Fees eventRates{25, 50};
    for (const auto fees : {defaults, eventRates}) {
        std::cout << feeFor(Loan::Ordinary, 2, fees) << ' '
                  << feeFor(Loan::Oversize, 1, fees) << '\n';
    }
}
