#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class Widget {
public:
	virtual ~Widget() = default;
	virtual std::string render() const = 0;
};

class MetricCard final : public Widget {
public:
	MetricCard(std::string label, std::string value, std::string accent)
		: label_(std::move(label)), value_(std::move(value)), accent_(std::move(accent)) {}

	std::string render() const override {
		return "[metric] " + label_ + ": " + value_ + " accent=" + accent_;
	}

private:
	std::string label_;
	std::string value_;
	std::string accent_;
};

class ActionButton final : public Widget {
public:
	ActionButton(std::string title, std::string surface)
		: title_(std::move(title)), surface_(std::move(surface)) {}

	std::string render() const override {
		return "[button] " + title_ + " surface=" + surface_;
	}

private:
	std::string title_;
	std::string surface_;
};

class ThemeFactory {
public:
	virtual ~ThemeFactory() = default;
	virtual std::string accent() const = 0;
	virtual std::string surface() const = 0;
};

class LightThemeFactory final : public ThemeFactory {
public:
	std::string accent() const override { return "sky"; }
	std::string surface() const override { return "paper"; }
};

class DarkThemeFactory final : public ThemeFactory {
public:
	std::string accent() const override { return "lime"; }
	std::string surface() const override { return "slate"; }
};

class DashboardBuilder {
public:
	explicit DashboardBuilder(const ThemeFactory& theme) : theme_(theme) {}

	DashboardBuilder& addMetricCard(const std::string& label, const std::string& value) {
		widgets_.push_back(std::make_unique<MetricCard>(label, value, theme_.accent()));
		return *this;
	}

	DashboardBuilder& addActionButton(const std::string& title) {
		widgets_.push_back(std::make_unique<ActionButton>(title, theme_.surface()));
		return *this;
	}

	void render(std::ostream& out) const {
		for (const auto& widget : widgets_) {
			out << widget->render() << '\n';
		}
	}

private:
	const ThemeFactory& theme_;
	std::vector<std::unique_ptr<Widget>> widgets_;
};

int main() {
	std::unique_ptr<ThemeFactory> theme = std::make_unique<DarkThemeFactory>();

	DashboardBuilder builder(*theme);
	builder
		.addMetricCard("Active users", "184")
		.addMetricCard("Build queue", "9")
		.addActionButton("Flush cache");

	std::cout << "Starter dashboard\n";
	builder.render(std::cout);
	std::cout << "\nTODO: add a second factory family or a richer builder step when the UI must vary by environment.\n";
}
