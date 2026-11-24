# Title formatter

Build the supplied formatter library, its demo and its checks. The empty input already works. Implement word-start capitalization in formatter.cpp while preserving every space, tab and existing letter inside a word. Restrict the exercise to ASCII text.

The reference passes all three checks. Compare the implementation to the predictions from the starter.

From this directory, run:

```sh
cmake -S . -B cmake-build -DCMAKE_BUILD_TYPE=Debug
cmake --build cmake-build
ctest --test-dir cmake-build --output-on-failure
```

Use separate build directories for the starter and reference.
