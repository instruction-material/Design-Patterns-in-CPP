# Register a second CMake target

The demo converts 3 cm to 30 mm. Run ctest --test-dir cmake-build -N to count registered tests. The completed build has one. Add the length_checks executable from checks.cpp, link it to the same length library used by the demo and register it using add_test. Configure and build again. Temporarily change the multiplier to 100. Observe the check fail, restore 10 and verify the check passes.

From this directory, run:

```sh
cmake -S . -B cmake-build -DCMAKE_BUILD_TYPE=Debug
cmake --build cmake-build
ctest --test-dir cmake-build --output-on-failure
```

Use separate build directories for the starter and reference.
