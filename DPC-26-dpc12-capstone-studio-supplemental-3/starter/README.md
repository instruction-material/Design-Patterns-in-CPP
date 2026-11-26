# Capstone Extension Practice

The supply desk records requests by ID in arrival order. Extend submit to put an urgent request ahead of every ordinary request while maintaining arrival order within each group. An ID already in the queue is rejected and keeps its original position and priority. Work on the queue operation while leaving the display code unchanged.

From either role folder, build and run with a C++20 compiler.

```sh
c++ -std=c++20 -Wall -Wextra -pedantic main.cpp -o practice
./practice
```

## Checkpoints

Submit ordinary A, urgent B, ordinary C and urgent D. The result is B, D, A, C. Submit urgent A again and verify it returns false and the order stays fixed. Try an all-ordinary queue and an all-urgent queue and check that each keeps its original arrival order. Explain where the new insertion rule lives and how the existing duplicate rule still applies.
