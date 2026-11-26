# Raw Pointer Refactor Extension Practice

The preview function allocates a receipt and passes the owning pointer back to its caller. The caller adopts it immediately with a unique pointer. Replace that API with a value return and update the caller to print the value directly. A receipt is a snapshot of the booking title and seat count, valid independently of what happens to the booking.

From either role folder, build and run with a C++20 compiler.

```sh
c++ -std=c++20 -Wall -Wextra -pedantic main.cpp -o practice
./practice
```

## Checkpoints

Both versions print Morning drawing: 2. Keep one receipt, change the booking title and seat count, and make a second receipt. The original still shows the original title and 2 seats. Draw the lifetime of the booking and both receipt variables. Verify that the revised function returns Receipt by value.
