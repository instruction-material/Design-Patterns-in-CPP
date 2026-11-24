# A shipping quote without object slicing

A quote uses one of several shipping policies chosen at runtime. The starter copies the selected policy into a base object. Trace how that copy loses the derived behavior. Preserve dynamic dispatch and the caller-owned lifetime without allocating or copying a policy inside quote.

This reference passes the comparisons in main. Use them to trace the behavior of a copy and a call.

```sh
c++ -std=c++20 -Wall -Wextra -Wpedantic main.cpp -o lab && ./lab
```

For comparison, write a templated quote for a policy selected at compile time. A type with a compatible cents method can participate without inheriting from Rate. Test the same boundary inputs and explain which interface can accept different derived rates through the same base reference at runtime.
