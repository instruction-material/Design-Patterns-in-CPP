# Strategy Policy Transfer Practice

Build a print scheduler that can select its scheduling strategy when the program starts. Run the starter with no argument for arrival order, then with shortest for shortest-job-first. Both modes currently select the first pending job. Complete ShortestJob so it compares durations each time the scheduler needs a job. Preserve arrival order among jobs with equal durations. Leave the queue and output loop independent of the strategy selected by the caller.

## Checkpoints

The demo queue contains poster (8), card (2), label (2) and map (5). Arrival order is poster, card, label, map. Shortest order is card, label, map, poster. Try a single job and an empty queue, then explain which part owns the pending jobs and which part only inspects them.

Build and run from the downloaded folder:

```sh
c++ -std=c++20 -Wall -Wextra -pedantic main.cpp -o practice
./practice
```
