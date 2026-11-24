# Trace a temperature average

Build with debug symbols. Set a breakpoint at mean_temperature in temperature.cpp. Compare the sum, quotient and returned value for the three supplied pairs. Correct integer truncation, then explain why converting after division leaves the fractional part lost. Open starter first. Its two failing checks are intentional. Open solution for the independently buildable comparison after the exercise. Run the commands below from either role folder.

From this directory, run:

```sh
cmake -S . -B cmake-build -DCMAKE_BUILD_TYPE=Debug
cmake --build cmake-build
ctest --test-dir cmake-build --output-on-failure
```

Use separate build directories for the starter and reference.
