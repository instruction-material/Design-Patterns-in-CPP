#pragma once

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
        : label_(std::move(label)), value_(std::move(value)),
          accent_(std::move(accent)) {
    }

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
        : title_(std::move(title)), surface_(std::move(surface)) {
    }

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
        : title_(std::move(title)), accent_(std::move(accent)) {
    }

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
    virtual std::unique_ptr<Widget> makeMetric(const std::string& label,
                                               const std::string& value) const = 0;
    virtual std::unique_ptr<Widget> makeButton(const std::string& title) const = 0;
    virtual std::unique_ptr<Widget> makeBadge(const std::string& title) const = 0;
};

class LightThemeFactory final : public ThemeFactory {
  public:
    std::unique_ptr<Widget> makeMetric(const std::string& label,
                                       const std::string& value) const override {
        return std::make_unique<MetricCard>(label, value, "sky");
    }
    std::unique_ptr<Widget> makeButton(const std::string& title) const override {
        return std::make_unique<ActionButton>(title, "paper");
    }
    std::unique_ptr<Widget> makeBadge(const std::string& title) const override {
        return std::make_unique<StatusBadge>(title, "emerald");
    }
};

class DarkThemeFactory final : public ThemeFactory {
  public:
    std::unique_ptr<Widget> makeMetric(const std::string& label,
                                       const std::string& value) const override {
        return std::make_unique<MetricCard>(label, value, "lime");
    }
    std::unique_ptr<Widget> makeButton(const std::string& title) const override {
        return std::make_unique<ActionButton>(title, "slate");
    }
    std::unique_ptr<Widget> makeBadge(const std::string& title) const override {
        return std::make_unique<StatusBadge>(title, "amber");
    }
};

class DashboardBuilder {
  public:
    explicit DashboardBuilder(const ThemeFactory& theme) : theme_(theme) {
    }

    DashboardBuilder& addMetricCard(const std::string& label,
                                    const std::string& value) {
        widgets_.push_back(theme_.makeMetric(label, value));
        return *this;
    }

    DashboardBuilder& addActionButton(const std::string& title) {
        widgets_.push_back(theme_.makeButton(title));
        return *this;
    }

    DashboardBuilder& addStatusBadge(const std::string& title) {
        widgets_.push_back(theme_.makeBadge(title));
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

inline DashboardBuilder buildStandardDashboard(const ThemeFactory& theme) {
    DashboardBuilder builder(theme);
    builder.addMetricCard("Active users", "184")
        .addMetricCard("Build queue", "9")
        .addStatusBadge("Healthy")
        .addActionButton("Flush cache");
    return builder;
}
