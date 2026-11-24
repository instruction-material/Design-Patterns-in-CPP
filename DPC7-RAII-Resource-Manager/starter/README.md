# Texture lifetime and cleanup

The starter already owns each simulated texture through a move-only TextureHandle. PreviewRenderer hides its storage in Impl. Build the program and trace the acquire, draw and release lines.

## Assignment

Add terrain twice with player between the two requests. Display three entries while acquiring only two resources. Keep the cache inside Impl. Each displayed entry must refer to a texture that stays alive for the full draw. Keep the public PreviewRenderer interface and the move-only handle contract intact.

Add a scope-exit guard to draw. Its callback must run once on normal exit and when an exception leaves the scope. Give the guard one owner. If it can move, transferring the guard must leave the original inactive. The cleanup callback must not throw.

Build in the extracted project folder:

```sh
c++ -std=c++20 -Wall -Wextra -Wpedantic main.cpp -o textures
./textures
```

Expect terrain#1 player#2 terrain#1 in the draw, one acquisition and one release per distinct label, and one draw-finished callback. Use a counter in a separate scope to verify that moving the guard does not repeat the callback. Repeat with an exception caught outside that scope.
