# Refactoring Capstone Project

A classroom kit report counts ready pieces and pieces awaiting repair. The starter counts directly inside main. Move the counting into summarize and have main pass its result to print. Each record contributes its positive quantity to the corresponding category. Keep the supplied ready and repair output identical.

From either role folder, build and run with a C++20 compiler.

```sh
c++ -std=c++20 -Wall -Wextra -pedantic main.cpp -o practice
./practice
```

## Checkpoints

The sample combines two Ready rows (2 and 3) and one Repair row (1). Confirm the report stays ready=5 and repair=1. Test an empty input and a zero-quantity row by calling summarize independently from the printer.

## Refactoring Capstone Extension Challenge

After the original two counts are correct, include Retired as a third category. Expose retired in the returned summary and use print’s optional flag to show the third count only when requested. Preserve the ordinary two-line output.

Add three retired pieces and request the extended output. The last line is retired=3 and the original counts remain unchanged. A negative quantity contributes nothing. Run the original output check once again.
