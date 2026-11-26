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
        int seat = 0;
        const char* end = slip.seatText.data() + slip.seatText.size();
        const auto parsed = std::from_chars(slip.seatText.data(), end, seat);
        if (parsed.ec != std::errc{} || parsed.ptr != end) return false;
        return reserve({slip.label, seat});
    }

    bool withdraw(int seat) {
        return std::erase_if(guests_, [seat](const Guest& guest) {
            return guest.seat == seat;
        }) != 0;
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
