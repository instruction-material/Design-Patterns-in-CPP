# Structural Boundary Extension Practice

A catalogue returns either a title or an empty optional for a missing number. Complete Memo::find so repeated lookups for an ID reuse the first result. Cache successful and missing results. The supplied clear operation resets the memo so the next lookup goes back to the catalogue.

From either role folder, build and run with a C++20 compiler.

```sh
c++ -std=c++20 -Wall -Wextra -pedantic main.cpp -o practice
./practice
```

## Checkpoints

Read title 7 twice and missing ID 9 twice. Exactly two source calls are needed before clearing. Clear, then read 7 and verify a third source call. Compare a recorded empty title with a missing ID.
