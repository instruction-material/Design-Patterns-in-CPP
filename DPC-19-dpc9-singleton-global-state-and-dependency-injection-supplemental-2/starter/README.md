# Reservation expiry with a replaceable clock

A seat reservation expires at its deadline. Change Reservation to read the borrowed Clock on each call. Replace the fixed legacy time source and make each reservation follow its own clock. Use integer minutes and treat the deadline itself as expired.

From this folder, run:

```sh
c++ -std=c++20 -Wall -Wextra -Wpedantic main.cpp -o lab && ./lab
```

The original program compiles. The failing checks print the observed and expected results. Keep the checks in main as the behavior contract while changing the implementation.

Add a second reservation with an earlier deadline on the same clock. Predict both results before advancing time and again after advancing it. Explain how the test runs without waiting in real time.
