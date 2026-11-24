# A factory method for label printing

A print job frames a shipping label in square brackets. Domestic and international jobs share the framing workflow but create different formatters. Route creation through the virtual makeFormatter method, use the product through its Formatter interface, and preserve ownership with unique_ptr. Keep PrintJob free of country-specific branches.

This starter builds. Its checks print the observed and expected results. Fix the implementation and keep the checks.

```sh
c++ -std=c++20 -Wall -Wextra -Wpedantic main.cpp -o lab && ./lab
```

Add a third job and formatter for a pickup label. The receiving code must be able to call the existing PrintJob::print without knowing its concrete job type.
