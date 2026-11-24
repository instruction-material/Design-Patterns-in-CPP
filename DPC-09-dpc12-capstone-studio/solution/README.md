# Asset inventory import capstone

A level editor imports quantities of named assets from batches of text. The command reads one batch from standard input and prints a sorted inventory. The library can receive several batches on the same Inventory. A rejected batch must leave the previous inventory unchanged.

## Establish the baseline

From the extracted folder:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
ctest --test-dir build -L baseline --output-on-failure
ctest --test-dir build -L feature --output-on-failure
printf 'tile 2\nhero 1\ntile 3\n' | ./build/asset_import space
```

The last command prints hero=1 then tile=5 on separate lines. The reference passes all six cases. Record the exact output, the four green baseline cases and the feature test results. On Windows with a multi-configuration generator, build with `--config Debug`, add `-C Debug` to CTest and run the executable under build/Debug.

## Refactor while retaining behavior

Follow a row from main.cpp through Inventory::import in importer.cpp to the report. Draw the lifetime of the caller's stream, each parsed record, the pending inventory and the committed inventory. Mark the point at which a batch becomes visible. Use the smallest input that exercises a valid row followed by a malformed row. Check that neither change appears after rejection.

Separate parsing from accumulation using the existing tests. Commit that refactor while the baseline is still green. Document one concrete change that becomes local to the parser. Compare a callable selected at runtime with a virtual parser interface and choose one. Explain whether either design needs dynamic allocation.

## Add a second input format

The space format accepts two whitespace-separated tokens. The comma format requires exactly one comma and no spaces around it. Names consist of lowercase ASCII letters, digits and underscores. Quantities range from 1 through 10000; cumulative totals cannot exceed 1000000. Empty lines may be skipped. Preserve sorted output, accumulation of duplicate names and all-or-nothing updates in both formats. This comma grammar covers two simple fields; quoted CSV fields are outside the assignment.

Make both feature tests pass. Add one new test for a malformed final row and one for an upper bound. Run all six supplied tests before and after the change. Pipe `hero,2` and `tile,5` on separate lines to the comma command and compare it with the same data in space format.

## Handoff and rollback

Submit the edited files, tests, a before/after ownership diagram and one paragraph explaining the chosen boundary and the alternative. Keep separate baseline, refactor and feature revisions. Revert the feature on a separate branch and show the space pipeline still passes. With a compiler that supports them, run the checks again in a clean build with AddressSanitizer and UndefinedBehaviorSanitizer; record the command, actual results and any unsupported runtime.
