# Iterator Boundary Extension Practice

Use a read-only cursor to visit a static outline in breadth-first order. Build main.cpp with C++20. The starter can take the first node from a queue and report exhaustion, but only the root ever enters the queue. Before returning the current node, append its children at the back in their original order. Store borrowed pointers in the queue. Keep the source outline alive and fixed for the entire traversal.

## Checkpoints

The sample order is Course, Week 1, Week 2, Arrays, Loops, Grid. Test a one-node tree and call next twice after exhaustion. Both calls return null. Start two cursors on the same outline and advance one; the other remains at the root. Explain what would be invalidated if the caller rebuilt a child vector during traversal.

```sh
c++ -std=c++20 -Wall -Wextra -pedantic main.cpp -o practice
./practice
```
