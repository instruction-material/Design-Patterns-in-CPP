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

class Reservation {
public:
    Reservation(const Clock& clock, int deadline) : clock_(clock), deadline_(deadline) {}
    bool expired() const { return clock_.minute() >= deadline_; }
private:
    const Clock& clock_;
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
