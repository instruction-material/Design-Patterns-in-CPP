# Structural Wrapper Transfer Practice

Wrap a notice sink with a decorator that records the result of each delivery. NoticeSink is the shared interface. A line can be accepted or rejected. Complete TracingSink::deliver so it forwards the original line once, then records one accepted or rejected entry and returns the wrapped sink’s result. This decorator borrows its sink and trace. Keep those objects alive during its use.

From either role folder, build and run with a C++20 compiler.

```sh
c++ -std=c++20 -Wall -Wextra -pedantic main.cpp -o practice
./practice
```

## Checkpoints

Deliver an ordinary note and an empty note. The plain sink accepts the first and rejects the second. The trace records both outcomes in order. Try two identical notes and verify that there are two calls and two entries. Compose two decorators around one sink and verify that the real sink still receives only one call per message.
