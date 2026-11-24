#include <iostream>

class Clock {
public:
    virtual ~Clock() = default;
    virtual int minute() const = 0;
};

class ManualClock final : public Clock {
public:
    explicit ManualClock(int initial) : value(initial) {}
    int minute() const override { return value; }
    void advance() { ++value; }
private:
    int value;
};

int legacyMinute() { return 9; }

class Reservation {
public:
    // TODO: retain the clock and evaluate the deadline against its current time.
    Reservation(const Clock&, int deadline) : deadline_(deadline) {}
    bool expired() const { return legacyMinute() >= deadline_; }
private:
    int deadline_;
};

bool check(const char* label, int actual, int expected) {
    std::cout << label << ": observed " << actual << ", expected " << expected << '\n';
    return actual == expected;
}

int main() {
    ManualClock local(9), remote(8);
    Reservation hold(local, 10), other(remote, 10);
    bool ok = check("before deadline", hold.expired(), false);
    local.advance();
    ok &= check("at deadline", hold.expired(), true);
    ok &= check("separate clock", other.expired(), false);
    local.advance();
    ok &= check("after deadline", hold.expired(), true);
    return ok ? 0 : 1;
}
