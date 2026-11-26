# Facade Boundary Extension Practice

The audio tour facade coordinates a track catalog and a player. The caller gives a stop name and a volume from 0 to 100 inclusive. Implement AudioGuide::start. Reject an invalid volume before searching the catalog. If the name has no track ID, return UnknownStop without calling the player. Otherwise pass the looked-up ID and the requested volume to the player exactly once and return Started.

From either role folder, build and run with a C++20 compiler.

```sh
c++ -std=c++20 -Wall -Wextra -pedantic main.cpp -o practice
./practice
```

## Checkpoints

Try the garden at volume 50, an unknown stop and the garden at volume 110. Only the garden at 50 reaches the player. Test the inclusive volume limits of 0 and 100 and check that the same track can start twice. Imagine changing the value stored for the garden. The caller should still pass only the name and volume.
