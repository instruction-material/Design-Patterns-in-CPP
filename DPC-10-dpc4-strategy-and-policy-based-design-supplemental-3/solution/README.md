# Policy Design Extension Practice

Build a temperature alarm whose threshold and comparison rule are fixed by its type. The starter passes each integer reading to the policy selected by a template argument. AtLeast<30> already includes its boundary. Implement OutsideBand<Low, High> so it flags values strictly outside the inclusive range. Require the lower limit to be no greater than the upper limit at compile time. The same filtering function should work with either policy without a switch.

## Checkpoints

For readings 9, 10, 20, 30 and 31, AtLeast<30> reports 30 and 31. OutsideBand<10, 30> reports 9 and 31. Try a zero-width band and an empty sample. Show where the compiler fixes the rule and where the running program supplies the data.

Build and run from the downloaded folder:

```sh
c++ -std=c++20 -Wall -Wextra -pedantic main.cpp -o practice
./practice
```
