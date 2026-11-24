# Dashboard reference

Compile main.cpp with the dashboard.hpp file alongside it. Run `c++ -std=c++20 -Wall -Wextra -Wpedantic main.cpp -o dashboard && ./dashboard`. The two dashboards have the same four rows. Their distinct metric, badge and button styles come from the selected family.

In dashboard.hpp, compare the owning unique_ptr returned by makeMetric with the borrowed ThemeFactory reference held by DashboardBuilder. The creation methods choose the products. The builder records their order and buildStandardDashboard supplies the shared assembly steps. main.cpp owns each factory until its dashboard has been built.

For a transfer check, implement a plain-text widget family, pass it to buildStandardDashboard, and verify that its four products appear in the original order.
