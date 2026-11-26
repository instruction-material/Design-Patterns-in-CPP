# Ownership Refactor Transfer Practice

An equipment desk owns a checkout record for the duration of a loan. A display receives a weak pointer so it can show the current record without owning it. Complete Display::show. Lock the weak pointer to read a live label and return "(returned)" when no record is live. Keep the owning handle local to the call.

From either role folder, build and run with a C++20 compiler.

```sh
c++ -std=c++20 -Wall -Wextra -pedantic main.cpp -o practice
./practice
```

## Checkpoints

Display a live tripod checkout, then reset the desk’s owning pointer. The display changes to "(returned)". Verify the owner count is one after show returns. Construct an empty display and verify it also reports "(returned)".
