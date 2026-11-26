# Pattern Adaptation Extension Practice

A local exhibit tour has two kinds of steps: show a card or pause for a number of seconds. The input vector can contain both in any order. Build main.cpp with C++20 and trace the two describe overloads. Implement render by visiting the active alternative in the variant and returning the string from the matching overload. An exhibit step is a value and can be copied independently of its original.

## Checkpoints

The demo displays Welcome, pauses for 3 seconds, and displays Map. Add a pause of zero seconds and an empty string card to verify dispatch remains based on the active type. Copy a step, edit the original card title, and confirm the copied step retains its title. Explain where a closed variant works well and what changes when a third step type is added.

```sh
c++ -std=c++20 -Wall -Wextra -pedantic main.cpp -o practice
./practice
```
