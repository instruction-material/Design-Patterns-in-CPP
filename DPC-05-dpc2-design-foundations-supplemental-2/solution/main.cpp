#include <initializer_list>
#include <iostream>
#include <optional>

struct Probe {
    virtual ~Probe() = default;
    virtual std::optional<int> read() const = 0;
};

struct FixedProbe final : Probe {
    int reading;
    explicit FixedProbe(int value) : reading(value) {}
    std::optional<int> read() const override { return reading; }
};

struct OfflineProbe final : Probe {
    std::optional<int> read() const override { return std::nullopt; }
};

enum class Status { Missing, Below, Ready };

Status inspect(const Probe& probe, int minimum) {
    const auto value = probe.read();
    if (!value) return Status::Missing;
    return *value < minimum ? Status::Below : Status::Ready;
}

const char* label(Status status) {
    switch (status) {
        case Status::Missing: return "Missing";
        case Status::Below: return "Below";
        case Status::Ready: return "Ready";
    }
    return "Unknown";
}

int main() {
    const FixedProbe atLimit(10), below(9);
    const OfflineProbe unplugged;
    for (const Probe* probe : {static_cast<const Probe*>(&atLimit),
                               static_cast<const Probe*>(&below),
                               static_cast<const Probe*>(&unplugged)}) {
        std::cout << label(inspect(*probe, 10)) << '\n';
    }
}
