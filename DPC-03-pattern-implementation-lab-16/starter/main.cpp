#include <algorithm>
#include <charconv>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

struct DeskSlip {
    std::string label;
    int seat;
};

struct MailSlip {
    std::string label;
    std::string seatText;
};

struct Guest {
    std::string label;
    int seat;
};

class Workshop {
public:
    bool admit(const DeskSlip& slip) {
        return reserve({slip.label, slip.seat});
    }

    bool admit(const MailSlip& slip) {
        (void)slip;
        return false; // TODO: Adapt the textual seat.
    }

    bool withdraw(int seat) {
        (void)seat;
        return false; // TODO: Remove only the matching booking.
    }

    const std::vector<Guest>& guests() const { return guests_; }

private:
    bool reserve(Guest guest) {
        if (guest.label.empty() || guest.seat < 1 || guest.seat > 12) return false;
        if (std::ranges::any_of(guests_, [&guest](const Guest& held) {
            return held.seat == guest.seat;
        })) return false;
        guests_.push_back(std::move(guest));
        return true;
    }

    std::vector<Guest> guests_;
};

int main() {
    Workshop workshop;
    std::cout << std::boolalpha;
    const bool desk = workshop.admit(DeskSlip{"Ada", 2});
    const bool mail = workshop.admit(MailSlip{"Mina", "3"});
    const bool invalid = workshop.admit(MailSlip{"Jo", "3x"});
    std::cout << desk << ' ' << mail << ' ' << invalid << '\n';
    const bool first = workshop.withdraw(2);
    const bool second = workshop.withdraw(2);
    const bool reused = workshop.admit(MailSlip{"Jo", "2"});
    std::cout << first << ' ' << second << ' ' << reused << '\n';
    for (const auto& guest : workshop.guests()) std::cout << guest.label << ':' << guest.seat << '\n';
}
