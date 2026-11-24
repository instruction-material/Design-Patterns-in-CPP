# Quoted editor commands

Compile with `c++ -std=c++20 -Wall -Wextra -pedantic main.cpp -o editor` and run `./editor`. Enter one command per line. The input loop ends at end of file.

The running editor already handles mode, queue execution and undo. Complete the scanner in `parseLine` so it also accepts `append "some text"` and `replace "new text"`. Use `std::quoted` for spaces, escaped quotes and empty strings. Check the opening quote explicitly. The scanner must reject unknown verbs, missing quotes, unfinished strings and extra tokens. A syntax error leaves the session untouched.

Try the following input:

```text
append "first draft"
mode review
replace "blocked"
append "!"
undo
```

The final document is `first draft`. A valid replace in review mode reaches the editor and is rejected there. An unquoted argument prints `Syntax error` before the editor sees a command.
