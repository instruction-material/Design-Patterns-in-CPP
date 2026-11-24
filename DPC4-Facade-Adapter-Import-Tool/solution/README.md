# Import records from two formats

From this folder, run `cmake -S . -B build`, `cmake --build build`, then `./build/import_records`.
The legacy text format uses one unquoted label, category and nonnegative integer quantity per line, separated by commas. Blank lines are skipped. The example reports terrain, player and music.

Give the facade a common input interface. Implement a second adapter that accepts one JSON object per line with nonempty string fields `label` and `category` and an integer `quantity` from zero through the platform's maximum int. Use a JSON parser for escapes, whitespace and field ordering. Keep format handling inside each adapter. Report a malformed batch as an error before returning any records.

Try `lamp,prop,3` and `{"quantity":3, "category":"prop", "label":"lamp"}`. Both must produce the same record. Try a quoted quantity or a trailing extra CSV field; both must fail.

The JSON adapter uses json-c 0.15 or newer. On macOS install `brew install cmake pkgconf json-c`. On Debian or Ubuntu install `cmake pkg-config libjson-c-dev` with the system package manager.
