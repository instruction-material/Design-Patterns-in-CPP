# Design Patterns in C++

This folder is structured as the future
`instruction-material/Design-Patterns-in-CPP` repository.

The materials follow the core project sequence used by the site course:

1. `DPC1-Factories-and-Builders-Workshop`
2. `DPC2-Strategy-and-Policy-Simulator`
3. `DPC3-Observer-Event-Hub`
4. `DPC4-Facade-Adapter-Import-Tool`
5. `DPC5-Command-and-State-Editor`
6. `DPC6-Composite-Scene-Tree`
7. `DPC7-RAII-Resource-Manager`
8. `DPC8-Legacy-Refactor-Capstone`

Each project contains:

- `starter/` with a guided scaffold and TODO-style follow-up work
- `solution/` with a complete reference implementation
- `README.md` describing the design pressure and the target patterns

## Tooling

Preferred IDEs:

- `CLion`
- `VS Code`

Expected local toolchain:

- `clang++` or `g++`
- `cmake`
- `lldb` or `gdb`

The projects standardize on a simple CMake layout so students can work in
multi-file C++ instead of one-off snippets. Modern ownership and lifetime
habits are part of the design curriculum, not optional cleanup work.

## Local Validation Workflow

From this folder:

1. `cmake -S . -B build`
2. `cmake --build build`
3. Run the generated starter or solution binaries from `build/`

## Teaching Notes

- Compare the textbook version of each pattern against a modern C++ version.
- Ask students to justify stack versus heap, value versus polymorphic type, and
  ownership transfer explicitly.
- Use sanitizers and debugger runs whenever a design mistake could become a
  lifetime bug.
