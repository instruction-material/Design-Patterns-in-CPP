#include "dashboard.hpp"

int main() {
    std::vector<std::unique_ptr<ThemeFactory>> themes;
    themes.push_back(std::make_unique<LightThemeFactory>());
    themes.push_back(std::make_unique<DarkThemeFactory>());

    for (const auto& theme : themes) {
        const auto rows = buildStandardDashboard(*theme).build();
        std::cout << "Dashboard variant\n";
        for (const auto& row : rows) {
            std::cout << "  " << row << '\n';
        }
        std::cout << '\n';
    }
}
