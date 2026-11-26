# Resource Boundary Extension Practice

A drawing board owns its current labels. A FrameBatch stores proposed changes in a separate vector. Complete commit so it rejects an empty batch or one with an empty label and leaves the board unchanged. When every label is valid, swap the whole batch into the board, then finish the batch. A finished batch rejects another commit and any later append. The board must outlive the batch.

From either role folder, build and run with a C++20 compiler.

```sh
c++ -std=c++20 -Wall -Wextra -pedantic main.cpp -o practice
./practice
```

## Checkpoints

Propose a two-label replacement with one empty label and check that the original board remains visible. Use a fresh batch to replace the board with Map and Key. Call commit again and verify the new labels stay in order. Verify that destroying an uncommitted batch also leaves the board unchanged.
