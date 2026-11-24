# Independent event listings from one builder

A builder assembles a listing from a required nonempty title, a positive capacity and an optional room. Default to online with one seat. Return an empty optional for an invalid listing. Each successful build produces an independent value even when the builder is edited and reused.

This starter builds. Its checks print the observed and expected results. Fix the implementation and keep the checks.

```sh
c++ -std=c++20 -Wall -Wextra -Wpedantic main.cpp -o lab && ./lab
```

Try capacities of minus one and one. Change a room after the first build. Explain where validation happens and show that a previously built listing keeps its original room.
