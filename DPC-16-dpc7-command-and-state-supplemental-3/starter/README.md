# Redo across editor modes

Compile with `c++ -std=c++20 -Wall -Wextra -pedantic main.cpp -o editor` and run `./editor`. Undo already restores the previous document. Extend the editor with redo. Store undone commands in a second stack of unique owners. Reapply the most recently undone command only when the current mode permits it. A successful redo returns the command to history. An empty stack or a mode rejection preserves the document and both stacks.

A newly applied edit starts another history branch and clears redo. Enqueuing or rejecting an edit must preserve redo. The example first prints A, then AB after redo. A rejected replacement leaves redo available in review mode. The last line should contain AC, because the accepted C edit invalidated the discarded B branch. Add a two-level undo and redo case to check the order.
