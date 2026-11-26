# Modern Ownership Transfer Practice

The inbox owns a draft through a unique pointer. Its preview is a borrowed read-only pointer valid while that draft stays in the inbox. Build the starter with C++20. Implement take so it hands ownership of the exact draft to a caller and leaves the inbox empty. Use the returned owner for subsequent access. The member pointer already records whether the inbox contains a draft.

## Checkpoints

The sample previews Sketch, takes it, and reads the same title through the returned owner. Check that the inbox is empty after transfer and a second take returns an empty pointer. Rename the transferred draft and place it into a new inbox. Draw which variable owns the draft before take, after take, and after the final move.

```sh
c++ -std=c++20 -Wall -Wextra -pedantic main.cpp -o practice
./practice
```
