#include <cstddef>
#include <iostream>
#include <memory>
#include <utility>

struct CountRelease {
    int& releases;

    void operator()(int* value) const noexcept {
        delete[] value;
        ++releases;
    }
};

using Buffer = std::unique_ptr<int[], CountRelease>;

Buffer open(std::size_t size, int& releases) {
    if (size == 0) return Buffer(nullptr, CountRelease{releases});
    return Buffer(new int[size]{}, CountRelease{releases});
}

int main() {
    int releases = 0;
    auto palette = open(3, releases);
    if (palette) palette[1] = 7;
    auto moved = std::move(palette);
    std::cout << (moved ? moved[1] : -1) << ' ' << std::boolalpha << !palette << '\n';
    moved.reset();
    std::cout << releases << '\n';
}
