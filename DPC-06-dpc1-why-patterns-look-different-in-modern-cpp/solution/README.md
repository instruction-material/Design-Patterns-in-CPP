# Independent scene presets

A scene preset stores an exposure setting and an ordered list of effect names. Copying a preset creates an independently editable variant. Preserve the public interface and default copy operations. Select storage that owns each value without shared mutable state or manual cleanup.

This reference passes the comparisons in main. Use them to trace the behavior of a copy and a call.

```sh
c++ -std=c++20 -Wall -Wextra -Wpedantic main.cpp -o lab && ./lab
```

Compare two alternatives: a heap-owned settings object with explicit deep copying, and settings stored by value. Identify who owns the data, when it is destroyed and how copying the effect list scales with its length. Add a variant of a variant and change both in different ways.
