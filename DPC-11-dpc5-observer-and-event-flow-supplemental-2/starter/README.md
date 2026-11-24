# Observer Event Transfer Practice

Route match events to interested listeners. A goal listener should receive goal events only, while a general match log can subscribe to all topics with an empty filter. The caller retains ownership of each listener. Implement publish using the subscription snapshot, the topic on each slot and its weak listener pointer. Deliver matching events in registration order. Releasing the caller’s last shared owner should end delivery to that listener.

## Checkpoints

Publish a goal and a foul with the scoreboard, referee and general log subscribed. The scoreboard records only the goal, the referee records only the foul and the log records both. Release the referee and publish another foul. The general log still receives it. Predict what happens for an unrecognized topic.

Build and run from the downloaded folder:

```sh
c++ -std=c++20 -Wall -Wextra -pedantic main.cpp -o practice
./practice
```
