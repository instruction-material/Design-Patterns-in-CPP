#include <iostream>
#include <string>

struct Booking {
    std::string title;
    int seats;
};

struct Receipt {
    std::string title;
    int seats;
};

Receipt preview(const Booking& booking) {
    return {booking.title, booking.seats};
}

void print(const Receipt& receipt) {
    std::cout << receipt.title << ": " << receipt.seats << '\n';
}

int main() {
    const Booking booking{"Morning drawing", 2};
    const Receipt receipt = preview(booking);
    print(receipt);
}
