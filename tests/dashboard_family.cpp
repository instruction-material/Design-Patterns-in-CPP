#include "../DPC1-Factories-and-Builders-Workshop/solution/dashboard.hpp"

class TextWidget final : public Widget {
  public:
    explicit TextWidget(std::string text) : text_(std::move(text)) {}
    std::string render() const override { return text_; }
  private:
    std::string text_;
};

class TextFactory final : public ThemeFactory {
  public:
    std::unique_ptr<Widget> makeMetric(const std::string& label,
                                       const std::string& value) const override {
        return std::make_unique<TextWidget>(label + "=" + value);
    }
    std::unique_ptr<Widget> makeButton(const std::string& title) const override {
        return std::make_unique<TextWidget>("action " + title);
    }
    std::unique_ptr<Widget> makeBadge(const std::string& title) const override {
        return std::make_unique<TextWidget>("status " + title);
    }
};

int main() {
    const TextFactory family;
    const std::vector<std::string> expected = {
        "Active users=184", "Build queue=9", "status Healthy", "action Flush cache"};
    return buildStandardDashboard(family).build() == expected ? 0 : 1;
}
