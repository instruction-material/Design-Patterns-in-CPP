# RAII Wrapper Transfer Practice

An output channel allows one active drawing window. The lease holds a reference to the channel, and the channel must outlive the lease. The constructor already tries to open the channel and stores the result. Implement the destructor so only a lease that acquired the channel closes it. The lease stays in its current scope and cannot be copied or moved.

From either role folder, build and run with a C++20 compiler.

```sh
c++ -std=c++20 -Wall -Wextra -pedantic main.cpp -o practice
./practice
```

## Checkpoints

Open one lease and attempt another while the channel is busy. The denied lease owns nothing, and leaving its scope must leave the channel open. Leaving the first lease’s scope closes the channel once. Create a successful lease and throw a simple exception inside that scope. After the catch, check that the channel is available again.
