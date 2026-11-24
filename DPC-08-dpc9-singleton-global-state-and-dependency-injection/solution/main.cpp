#include <iostream>

class Sequence {
public:
    int next() { return next_++; }
private:
    int next_ = 1;
};

class TicketDesk {
public:
    explicit TicketDesk(Sequence& sequence) : sequence_(sequence) {}
    int issue() { return sequence_.next(); }
private:
    Sequence& sequence_;
};

bool check(const char* label, int actual, int expected) {
    std::cout << label << ": observed " << actual << ", expected " << expected << '\n';
    return actual == expected;
}

int main() {
    Sequence north, south;
    TicketDesk intake(north), triage(north), pharmacy(south);
    bool ok = check("intake first", intake.issue(), 1);
    ok &= check("triage shares north", triage.issue(), 2);
    ok &= check("south starts fresh", pharmacy.issue(), 1);
    ok &= check("intake resumes", intake.issue(), 3);
    return ok ? 0 : 1;
}
