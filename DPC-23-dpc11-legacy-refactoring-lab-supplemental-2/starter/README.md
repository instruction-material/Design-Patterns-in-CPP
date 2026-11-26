# Legacy Refactor Transfer Practice

The workshop charges daily fees for late loans. The existing function has the default rates written in two branches. Build the starter and record the two default totals. Refactor feeFor so the Fees value supplied by the caller is the only source of rates and negative late days count as zero. Use an integer total in cents.

From either role folder, build and run with a C++20 compiler.

```sh
c++ -std=c++20 -Wall -Wextra -pedantic main.cpp -o practice
./practice
```

## Checkpoints

An ordinary loan at two late days costs 150 cents by default. An oversize loan at one late day costs 200 cents. Use 25 and 50 cents as alternate daily rates and verify that the same requests cost 50 and 50. On-time and early returns both cost zero. Explain which behavior the refactor preserves and which result changes only when the caller supplies new rates.
