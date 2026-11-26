# Runtime Variation Project

A gallery sign can show only a title or add its room number. SignPrinter receives a Style from its caller and borrows it. Complete text so it calls that style’s format method and returns the result. Keep selection outside the printer and keep both supplied styles alive while the printer uses them.

From either role folder, build and run with a C++20 compiler.

```sh
c++ -std=c++20 -Wall -Wextra -pedantic main.cpp -o practice
./practice
```

## Checkpoints

Pass the same print job to a brief style and a detailed style. For Maps in room 4 the formats are Maps and Maps (room 4). Add another job to confirm the printer uses the argument rather than a fixed room or title.

## Runtime Variation Extension Challenge

After printing with both existing styles works, implement use to switch an existing printer to a new style. Keep the displayed job and both strategies unchanged. Switching back restores the original formatting.

Trace the same Maps sign through brief, detailed and brief formatting. Test a different title and room after each switch. The printer borrows the current strategy, so the strategy must outlive each use.
