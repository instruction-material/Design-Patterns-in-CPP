#include <iostream>
#include <string>
#include <variant>
#include <vector>

struct Card { std::string label; };
struct Pause { unsigned seconds; };
using TourStep = std::variant<Card, Pause>;

std::string describe(const Card& card) { return "Show: " + card.label; }
std::string describe(const Pause& pause) { return "Pause: " + std::to_string(pause.seconds) + " seconds"; }

std::string render(const TourStep& step) {
    // TODO: use the overload for the active alternative.
    (void)step;
    return "(unrendered)";
}

int main() {
    const std::vector<TourStep> tour{Card{"Welcome"}, Pause{3}, Card{"Map"}};
    for (const auto& step : tour) std::cout << render(step) << '\n';
}
