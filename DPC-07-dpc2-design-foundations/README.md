# A shipping quote without object slicing

A quote uses one of several shipping policies chosen at runtime. The starter copies the selected policy into a base object. Trace how that copy loses the derived behavior. Preserve dynamic dispatch and the caller-owned lifetime without allocating or copying a policy inside quote.

Start in the starter folder and read its checks. The solution folder contains a working reference.
