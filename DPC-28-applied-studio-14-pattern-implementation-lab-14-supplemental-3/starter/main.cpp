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
    (void)size;
    return Buffer(nullptr, CountRelease{releases}); // TODO: Allocate the array.
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
