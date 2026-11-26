# Runtime Variation Extension Practice

A calibration session keeps caller-supplied rules as function objects. The session borrows no rule. Complete measure so it adds the active rule’s result to the stored total and returns the updated total. A replacement rule applies to future measurements. It leaves the accumulated total intact.

From either role folder, build and run with a C++20 compiler.

```sh
c++ -std=c++20 -Wall -Wextra -pedantic main.cpp -o practice
./practice
```

## Checkpoints

Start with the identity rule and measure 3. Replace the rule with one that adds 2 and measure 3 again. The totals are 3 and 8. Change the original offset variable after creating the replacement rule to verify it was captured by value. Swap back to identity and verify the total continues from 8.
