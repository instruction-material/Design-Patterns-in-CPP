# A factory method for label printing

A print job frames a shipping label in square brackets. Domestic and international jobs share the framing workflow but create different formatters. Route creation through the virtual makeFormatter method, use the product through its Formatter interface, and preserve ownership with unique_ptr. Keep PrintJob free of country-specific branches.

Each role folder includes a runnable program, the assignment and its checks.
