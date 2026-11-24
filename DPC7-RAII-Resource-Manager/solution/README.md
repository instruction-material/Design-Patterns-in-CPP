# Texture cache reference

Build in this folder with `c++ -std=c++20 -Wall -Wextra -Wpedantic main.cpp -o textures && ./textures`. Keep scope_exit.hpp alongside main.cpp.

The cache and display list share ownership of each cached texture, while TextureHandle itself remains move-only. A repeated terrain request adds another display entry referring to the same handle. Two acquisitions support three entries. Each distinct handle releases once when its last owner disappears. Release order is independent of the cache iteration order.

ScopeExit runs its callback when draw exits. Copying a guard would duplicate the cleanup obligation. Moving transfers the callback and empties the source. Assigning over a live guard is disabled. Use nonthrowing callbacks so unwinding can complete safely.

Transfer check: use a counter for the callback, move the guard into a nested scope and leave that scope by throwing an exception. Inspect the counter after catching the exception and after the original guard goes out of scope. Both readings must equal one.
