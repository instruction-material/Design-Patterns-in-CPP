# Ticket desks and shared counters

Two service desks in one clinic share a ticket sequence. A second clinic starts its own sequence. Replace the hidden global lookup in TicketDesk with a borrowed Sequence supplied at construction. The owner creates the sequence before the desks that use it.

From this folder, run:

```sh
c++ -std=c++20 -Wall -Wextra -Wpedantic main.cpp -o lab && ./lab
```

The original program compiles. The failing checks print the observed and expected results. Keep the checks in main as the behavior contract while changing the implementation.

Comparison exercise: add a temporary desk inside a nested scope. Predict the next ticket after the temporary desk is destroyed, then run the check. Identify what could leak between two clinic tests if every desk consulted a singleton.
