# Route export receipts to an owned stream

An exporter writes a receipt for each saved file. Two exports may need separate destinations. Remove the process-wide receipt stream. Borrow the output stream passed into Exporter and direct each receipt to its owner, preserving its spelling, newline and order.

Open the starter folder for the instructions and checks. The solution folder contains a working implementation.
