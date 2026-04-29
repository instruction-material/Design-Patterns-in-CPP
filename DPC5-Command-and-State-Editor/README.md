# DPC5 Command and State Editor

Focus:

- `Command`
- `State`
- action history and undo

Students build a tiny editor that behaves differently by mode and records user
actions through command objects instead of large control-flow branches.

## Extension: Parsed Commands

After the command objects and state objects work, strong students can add a
small CS236-style scanner layer:

- Turn lines such as `append "text"`, `replace "text"`, `mode review`, and
  `undo` into tokens.
- Convert valid token sequences into command objects.
- Let the current state decide whether each command is legal.
- Keep tokenization/parsing errors separate from command execution errors.
