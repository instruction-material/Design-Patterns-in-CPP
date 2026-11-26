# Interface Contract Transfer Practice

Compare a fixed reading and a missing reading behind one read-only probe interface. Build the starter with C++20. Implement inspect using the Probe reference passed in by the caller. Call read once. An absent reading produces Missing, a reading strictly below the limit produces Below, and all other readings produce Ready. Keep the concrete probe types out of the decision code.

## Checkpoints

At limit 10, the demo reports Ready for 10, Below for 9, and Missing when no reading exists. Test a real zero reading with both limit 1 and limit 0. An absent reading and a recorded zero have different meanings. Create a probe that counts its read calls and show that inspect requests exactly one sample.

```sh
c++ -std=c++20 -Wall -Wextra -pedantic main.cpp -o practice
./practice
```
