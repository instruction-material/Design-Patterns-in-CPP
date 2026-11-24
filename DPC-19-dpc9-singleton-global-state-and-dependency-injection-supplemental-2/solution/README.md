# Reservation expiry with a replaceable clock

A seat reservation expires at its deadline. Change Reservation to read the borrowed Clock on each call. Replace the fixed legacy time source and make each reservation follow its own clock. Use integer minutes and treat the deadline itself as expired.

From this folder, run:

```sh
c++ -std=c++20 -Wall -Wextra -Wpedantic main.cpp -o lab && ./lab
```

This reference passes every check in main. Trace which object owns each service and which object borrows it.

Add a second reservation with an earlier deadline on the same clock. Predict both results before advancing time and again after advancing it. Explain how the test runs without waiting in real time.
