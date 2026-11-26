# Refactoring Capstone Extension Practice

A document revision owns a sorted set of topic labels. Implement combined so it returns a fresh revision containing the union of both inputs. A label appears once even if both revisions contain it. Leave both inputs unchanged and keep reporting separate from the merge.

From either role folder, build and run with a C++20 compiler.

```sh
c++ -std=c++20 -Wall -Wextra -pedantic main.cpp -o practice
./practice
```

## Checkpoints

Merge draft and map with map and review. The result prints draft, map, review in order. Reversing the inputs gives the same labels. Merge with an empty revision and confirm that the input’s labels are preserved.
