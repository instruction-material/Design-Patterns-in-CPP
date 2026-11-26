# Ownership-Aware Refactor Project

A repair bench owns instruments delivered to it. Complete Bench::accept to move a supplied unique pointer into the container. An empty handle is rejected. Find returns a borrowed read-only pointer. The caller may read it while the bench still owns that instrument.

From either role folder, build and run with a C++20 compiler.

```sh
c++ -std=c++20 -Wall -Wextra -pedantic main.cpp -o practice
./practice
```

## Checkpoints

Move a lute and a drum into the bench. Both incoming handles become empty and the original object addresses can be found by name. An absent name gives nullptr. Predict what happens when the vector grows and explain why moving the handles preserves the stored objects.

## Ownership Refactor Extension Challenge

After accept is working, complete extract. Find the first matching instrument, move its handle to the return value, and erase the vacated entry. Return an empty handle when the name is missing. Keep unrelated entries in their original order.

Remove the lute, then look up the drum and try removing an absent name. The reference prints the recovered name, two successful absence checks and the remaining drum. Use the returned handle to read the lute after extraction.
