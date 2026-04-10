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

class StatusBadge final : public Widget {
public:
	StatusBadge(std::string title, std::string accent)
		: title_(std::move(title)), accent_(std::move(accent)) {}

	std::string render() const override {
		return "[badge] " + title_ + " accent=" + accent_;
	}

private:
	std::string title_;
	std::string accent_;
};

class ThemeFactory {
public:
	virtual ~ThemeFactory() = default;
	virtual std::string accent() const = 0;
	virtual std::string surface() const = 0;
	virtual std::string statusAccent() const = 0;
};

class LightThemeFactory final : public ThemeFactory {
public:
	std::string accent() const override { return "sky"; }
	std::string surface() const override { return "paper"; }
	std::string statusAccent() const override { return "emerald"; }
};

class DarkThemeFactory final : public ThemeFactory {
public:
	std::string accent() const override { return "lime"; }
	std::string surface() const override { return "slate"; }
	std::string statusAccent() const override { return "amber"; }
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

	DashboardBuilder& addStatusBadge(const std::string& title) {
		widgets_.push_back(std::make_unique<StatusBadge>(title, theme_.statusAccent()));
		return *this;
	}

	std::vector<std::string> build() const {
		std::vector<std::string> output;
		output.reserve(widgets_.size());
		for (const auto& widget : widgets_) {
			output.push_back(widget->render());
		}
		return output;
	}

private:
	const ThemeFactory& theme_;
	std::vector<std::unique_ptr<Widget>> widgets_;
};

DashboardBuilder buildStandardDashboard(const ThemeFactory& theme) {
	DashboardBuilder builder(theme);
	builder
		.addMetricCard("Active users", "184")
		.addMetricCard("Build queue", "9")
		.addStatusBadge("Healthy")
		.addActionButton("Flush cache");
	return builder;
}

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
