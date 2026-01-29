````markdown
Name: Anthony Candelas
Email: tsallinger2@unl.edu
Date: 03NOV2025
Lab/Task: Hack09 - String Utilities

Hack09 — String Utilities (C)
=================================

Overview
--------
This small assignment implements a handful of common string utilities to practice C string manipulation. The code is intentionally simple, well-documented, and easy to read.

Files
-----
- `string_utils.h` — public prototypes and short documentation.
- `string_utils.c` — implementations for the required functions.
- `stringTester.c` — a test driver demonstrating at least three cases per function.

Name: Anthony Candelas
Email: tsallinger2@unl.edu
Date: 03NOV2025
Lab/Task: Hack09 - String Utilities

# Hack09 — String Utilities (C)

## Overview
This small assignment implements a handful of common string utilities to practice C string manipulation. The code is intentionally simple, well-documented, and easy to read.

## Files
- `string_utils.h` — public prototypes and short documentation.
- `string_utils.c` — implementations for the required functions.
- `stringTester.c` — a test driver demonstrating at least three cases per function.

## Implemented functions
- `void replaceChar(char *s, char oldChar, char newChar);`
  - Replace occurrences of `oldChar` with `newChar` in-place.

- `char *replaceCharCopy(const char *s, char oldChar, char newChar);`
  - Return a newly allocated string where occurrences of `oldChar` are replaced by `newChar`. Caller must `free()`.

- `void removeChar(char *s, char c);`
  - Remove all instances of `c` from `s` in-place; remaining characters are shifted down.

- `char *removeCharCopy(const char *s, char c);`
  - Return a newly allocated copy of `s` with all instances of `c` removed. Memory is sized exactly; caller must `free()`.

- `char **lengthSplit(const char *s, int n);`
  - Split `s` into pieces of length `n` (final piece may be shorter). Returns an array of `char*` where each entry is a separately allocated string. Caller knows the number of pieces from `strlen(s)` and `n`, and must free both the strings and the array.

## Build and run
From the `C/Hacks/Hack09` directory run:

```bash
gcc -std=c99 stringTester.c string_utils.c -o stringTester
./stringTester
```

## Notes
- The test driver prints concise PASS/FAIL results for the `lengthSplit` function and shows transformed strings for the other functions. It frees all allocated memory used in tests.
- Edge cases: the copy functions return `NULL` when given `NULL` input or when allocation fails. `lengthSplit` returns `NULL` on `NULL` input or invalid `n`.

If you want more tests or a small unit-test harness (automated comparisons and exit codes), I can add a simple test framework next.
