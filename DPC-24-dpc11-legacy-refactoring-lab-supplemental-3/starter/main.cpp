#include <iostream>
#include <memory>
#include <string>

struct Booking {
    std::string title;
    int seats;
};

struct Receipt {
    std::string title;
    int seats;
};

// The caller owns this pointer. TODO: Return a snapshot value instead.
Receipt* preview(const Booking& booking) {
    return new Receipt{booking.title, booking.seats};
}

void print(const Receipt& receipt) {
    std::cout << receipt.title << ": " << receipt.seats << '\n';
}

int main() {
    const Booking booking{"Morning drawing", 2};
    const std::unique_ptr<Receipt> receipt(preview(booking));
    print(*receipt);
}
