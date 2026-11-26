# Capstone Architecture Transfer Practice

A studio planner takes an ordered list of proposed tasks and a minute budget. Complete buildPlan as a function that returns the selected titles and total minutes. Ignore tasks with nonpositive durations. Keep positive-duration tasks in input order and stop at the first one that cannot fit. A task that exactly fills the available time fits. Keep all display code in print.

From either role folder, build and run with a C++20 compiler.

```sh
c++ -std=c++20 -Wall -Wextra -pedantic main.cpp -o practice
./practice
```

## Checkpoints

For tasks of 15, 20 and 10 minutes and a 35-minute budget, the first two tasks fit. At 19 minutes, only the first fits. At 10 minutes, stop at the first task, even though a later task would fit. Try a zero budget, an empty list and a task with a negative estimate. Verify the result by calling buildPlan without capturing console output.
