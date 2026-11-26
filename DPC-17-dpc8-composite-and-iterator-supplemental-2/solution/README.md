# Composite Traversal Transfer Practice

Build the starter with C++20. A playlist owns tracks and can also own nested playlists. Track.totalSeconds returns its own duration. Implement Playlist.totalSeconds by asking each entry for its total through the common interface. A nested playlist reports its descendants through the same operation. Keep duration separate from the display name so two tracks with the same name can still contribute their own time.

## Checkpoints

The demo has a 120-second intro and a nested playlist containing tracks of 90 and 45 seconds, for a total of 255. An empty playlist contributes zero. Add a second track with the same name and a duration of 30 seconds, then predict the new total. Test a second level of nesting before comparing with the reference.

```sh
c++ -std=c++20 -Wall -Wextra -pedantic main.cpp -o practice
./practice
```
