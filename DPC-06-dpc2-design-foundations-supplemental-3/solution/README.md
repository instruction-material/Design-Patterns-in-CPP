# Move Semantics Extension Practice

A move-only slot lease releases its slot in the destructor. The move constructor already transfers a slot and makes the source lease empty. Build the starter and trace that constructor. Complete move assignment so it releases the destination’s existing slot before transferring the source slot. When the source and destination are the same object, keep the slot. The registry must outlive every lease.

## Checkpoints

The demo starts with two live slots. Assigning the first lease to the second by move leaves one live slot, and the source becomes empty. After both leases leave scope the registry has zero live slots. Also test assigning an empty moved-from lease and moving through an alias of the same object. Both cases preserve the expected release counts.

```sh
c++ -std=c++20 -Wall -Wextra -pedantic main.cpp -o practice
./practice
```
