# Structural Boundary Transfer Practice

A cutting list records pieces in centimetres. An older catalogue uses inches. Complete the InchCut adapter so it returns the same Cut structure as the metric path, preserves the label, and multiplies inches by 2.54. The report reads only normalized cuts.

From either role folder, build and run with a C++20 compiler.

```sh
c++ -std=c++20 -Wall -Wextra -pedantic main.cpp -o practice
./practice
```

## Checkpoints

The reference reports the metric Shelf (25.4 cm) and the ten-inch Door (25.4 cm) through one report function. Compare zero inches, half an inch and a larger value using a numeric tolerance. Keep unit conversion out of the report.
