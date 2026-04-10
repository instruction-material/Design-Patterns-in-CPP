#include <functional>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <utility>

struct Order {
	std::string tier;
	int daysEarly;
	double cartTotal;
};

class DiscountStrategy {
public:
	virtual ~DiscountStrategy() = default;
	virtual std::string name() const = 0;
	virtual double discountFor(const Order& order) const = 0;
};

class StudentDiscount final : public DiscountStrategy {
public:
	std::string name() const override { return "student"; }
	double discountFor(const Order& order) const override { return order.cartTotal * 0.15; }
};

class MemberDiscount final : public DiscountStrategy {
public:
	std::string name() const override { return "member"; }

	double discountFor(const Order& order) const override {
		const double loyaltyBoost = order.tier == "gold" ? 0.05 : 0.02;
		return order.cartTotal * loyaltyBoost;
	}
};

class LambdaDiscount final : public DiscountStrategy {
public:
	LambdaDiscount(std::string label, std::function<double(const Order&)> fn)
		: label_(std::move(label)), fn_(std::move(fn)) {}

	std::string name() const override { return label_; }
	double discountFor(const Order& order) const override { return fn_(order); }

private:
	std::string label_;
	std::function<double(const Order&)> fn_;
};

struct GroundPolicy {
	static double quote(const Order& order) {
		return 4.0 + (order.daysEarly < 2 ? 1.5 : 0.0);
	}
};

struct PriorityPolicy {
	static double quote(const Order& order) {
		return 9.0 + (order.daysEarly < 2 ? 3.0 : 1.0);
	}
};

template <typename ShippingPolicy>
class ShippingCalculator {
public:
	double estimate(const Order& order) const {
		return ShippingPolicy::quote(order);
	}
};

void printScenario(const DiscountStrategy& strategy, const Order& order) {
	const double savings = strategy.discountFor(order);
	std::cout
		<< strategy.name()
		<< " discount saves $"
		<< std::fixed
		<< std::setprecision(2)
		<< savings
		<< '\n';
}

int main() {
	const Order order{"gold", 1, 120.0};
	StudentDiscount student;
	MemberDiscount member;
	LambdaDiscount flashSale(
		"flash-sale",
		[](const Order& currentOrder) {
			return currentOrder.daysEarly <= 1 ? currentOrder.cartTotal * 0.08 : 0.0;
		}
	);
	ShippingCalculator<GroundPolicy> ground;
	ShippingCalculator<PriorityPolicy> priority;

	printScenario(student, order);
	printScenario(member, order);
	printScenario(flashSale, order);
	std::cout << "Ground policy: $" << ground.estimate(order) << '\n';
	std::cout << "Priority policy: $" << priority.estimate(order) << '\n';
	std::cout << "\nThe runtime strategy chooses discount behavior; the template policy chooses shipping behavior at compile time.\n";
}
