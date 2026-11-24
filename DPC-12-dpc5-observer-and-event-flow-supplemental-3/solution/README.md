# Listener Lifetime Extension Practice

Use a move-only connection to control how long a clock callback receives ticks. The connection owns a shared callback, while the clock keeps a weak reference to it. Moving a connection transfers that ownership. Destroying a connection already releases it. Implement explicit disconnect, then remove expired weak entries at the start of each tick. Preserve the snapshot so a callback attached during a tick starts with the following tick.

## Checkpoints

Move the first connection into a new variable. The moved-from connection must have no effect when disconnected. After explicitly disconnecting the new owner, only the second callback runs. When its scope ends, the next tick removes the final expired entry. Test a second disconnect and confirm the counts stay unchanged.

Build and run from the downloaded folder:

```sh
c++ -std=c++20 -Wall -Wextra -pedantic main.cpp -o practice
./practice
```
