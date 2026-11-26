# Ownership Refactor Extension Practice

A palette exposes a dynamically allocated array through Buffer, a unique pointer with a custom deleter. Implement open so a nonzero size produces a zero-initialized int array paired with CountRelease. A zero size yields an empty Buffer. The release counter must outlive every buffer.

From either role folder, build and run with a C++20 compiler.

```sh
c++ -std=c++20 -Wall -Wextra -pedantic main.cpp -o practice
./practice
```

## Checkpoints

Write a value to a three-slot buffer and move it into another handle. The moved-from handle becomes empty. Reset only the new owner and verify the counter increments once. Destroy an empty buffer and test a second independently allocated buffer.
