# Observer event hub

Build with `c++ -std=c++20 -Wall -Wextra -pedantic main.cpp -o hub` and run `./hub`.
The caller owns each listener. The hub holds weak pointers. A publication takes a snapshot of the subscription list so callbacks can subscribe another listener for the next event. Lock each weak pointer immediately before calling it. A listener destroyed before its turn receives nothing.

The summary listener keeps the three latest topics in arrival order. Its separate summary method lets the caller choose when to inspect that state. The hub removes expired subscriptions before delivery. Subscribe the console, escalation and summary listeners, publish three events, release the console and publish a fourth. The last summary should list the second, third and fourth topics. Test a severity of 3 and 4 to find the escalation boundary.
