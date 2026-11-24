# Route export receipts to an owned stream

An exporter writes a receipt for each saved file. Two exports may need separate destinations. Remove the process-wide receipt stream. Borrow the output stream passed into Exporter and direct each receipt to its owner, preserving its spelling, newline and order.

From this folder, run:

```sh
c++ -std=c++20 -Wall -Wextra -Wpedantic main.cpp -o lab && ./lab
```

The original program compiles. The failing checks print the observed and expected results. Keep the checks in main as the behavior contract while changing the implementation.

Add a third destination and destroy its exporter before inspecting its stream. Verify that another destination still accepts receipts. Describe which object must outlive the exporter.
