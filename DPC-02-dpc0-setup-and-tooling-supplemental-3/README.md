# Register a second CMake target

The starter builds a library and demo. Add the supplied checks as a separate target and register that target with CTest. The reference has the completed build definition. Run the commands below from either role folder.

From this directory, run:

```sh
cmake -S . -B cmake-build -DCMAKE_BUILD_TYPE=Debug
cmake --build cmake-build
ctest --test-dir cmake-build --output-on-failure
```

Use separate build directories for the starter and reference.
