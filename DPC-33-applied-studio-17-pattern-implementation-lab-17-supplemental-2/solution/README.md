# Refactoring Capstone Transfer Practice

A schedule lists nondecreasing appointment minutes. Extract longGaps from the existing console loop. Return each consecutive gap that strictly exceeds the supplied threshold, in chronological order. An empty or one-appointment schedule produces no gaps. Keep the original console report unchanged.

From either role folder, build and run with a C++20 compiler.

```sh
c++ -std=c++20 -Wall -Wextra -pedantic main.cpp -o practice
./practice
```

## Checkpoints

For minutes 3, 6, 16 and 19 at threshold 5, the report is 10. At threshold 10 no gap qualifies. At threshold 2 the returned vector is 3, 10, 3. Try repeated minutes and verify the original schedule is unchanged.
