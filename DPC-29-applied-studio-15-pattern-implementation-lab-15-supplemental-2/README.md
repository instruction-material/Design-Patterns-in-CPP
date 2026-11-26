# Runtime Variation Transfer Practice

A print queue has a title and priority for each job. Complete ordered so it makes a copy of the jobs and applies the comparator supplied by its caller. Use a stable sort so jobs that compare equal keep their arrival order. Leave the original queue unchanged.

From either role folder, build and run with a C++20 compiler.

```sh
c++ -std=c++20 -Wall -Wextra -pedantic main.cpp -o practice
./practice
```

## Checkpoints

Order the jobs by title, then by descending priority. For Kim priority 2, Ada priority 1, and Bo priority 2, the title order is Ada, Bo, Kim and the priority order is Kim, Bo, Ada. Verify that the first queue still starts with Kim.
