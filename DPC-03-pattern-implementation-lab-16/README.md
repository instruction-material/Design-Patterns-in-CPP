# Structural Boundary Project

A workshop receives seat requests at its desk and by mail. The desk passes a numeric seat, while mail supplies a seat as text. Both formats must reach reserve with one Guest value. Complete the mail adapter. Convert all characters to an integer and send the guest to the shared reservation operation.

From either role folder, build and run with a C++20 compiler.

```sh
c++ -std=c++20 -Wall -Wextra -pedantic main.cpp -o practice
./practice
```

## Checkpoints

A desk request for seat 2 and a mail request for seat 3 both work. Mail text 3x is invalid. A correctly formed request for an occupied seat fails regardless of source. The accepted guest list contains the same name and numeric seat for each format.

## Structural Boundary Extension Challenge

After the two routes share validation, complete withdraw using only its seat argument. Return false for an absent reservation. After a successful withdrawal, either source can reserve that seat again.

Withdraw seat 2, try it again, and submit a new mail request for 2. The first withdrawal succeeds, the second fails, and the new guest takes the freed seat. Existing bookings are preserved.
