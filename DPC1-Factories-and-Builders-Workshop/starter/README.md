# Factories and builders workshop

This starter renders a dark dashboard with two metrics and a button. Open its main.cpp and trace the call to addMetricCard. The theme supplies a color, but the builder still chooses and constructs MetricCard. A palette can vary a color. A factory can also vary which Widget implementation is returned.

## Assignment

1. Give ThemeFactory creation methods for a metric, an action button and a status badge. Each method returns a unique_ptr<Widget>. Light and dark factories each create a compatible set of products.
2. Have DashboardBuilder ask its factory to make each widget. Keep the widgets in insertion order and transfer ownership into the builder. The factory is borrowed and must outlive the builder.
3. Assemble the same dashboard twice: Active users (184), Build queue (9), Healthy, Flush cache. In the light theme, the metrics use sky, the badge emerald and the button paper. In the dark theme, use lime, amber and slate respectively.
4. Test a third factory whose widgets render as plain text. The same assembly steps must produce all four rows without changing DashboardBuilder. Explain where the program selects a family and where it decides the sequence of products.

Within either project folder run:

```sh
c++ -std=c++20 -Wall -Wextra -Wpedantic main.cpp -o dashboard
./dashboard
```
