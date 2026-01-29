Name: Anthony Candelas
Email: tsallinger2@unl.edu
Date: 03NOV2025
Lab/Task: Hack09 - String Utilities (Java)

Description:
This README documents the Java implementation of Hack09 string utilities
and highlights differences from the C version of the assignment.

What I implemented
- `StringUtils.replaceChar(String s, char oldChar, char newChar)` — returns a
  new String where every instance of `oldChar` is replaced by `newChar`.
- `StringUtils.removeChar(String s, char c)` — returns a new String with all
  instances of `c` removed.
- `StringUtils.lengthSplit(String s, int n)` — returns a `List<String>` of
  substrings of length `n` (the final substring may be shorter). Throws
  `IllegalArgumentException` if `s` is null or `n <= 0`.

Tests and verification
- `StringTester.java` includes at least three test cases per method, covers
  null and edge cases, and prints PASS/FAIL-style output for visual verification.
- I compiled and ran the tests locally:

  javac -d . Java/Hack09/StringUtils.java Java/Hack09/StringTester.java
  java unl.soc.StringTester

  The tester prints expected vs actual results and reports simple PASS lines
  for matching outputs. The tester now exits with code 0 when all tests pass
  and exits with a non-zero status when any test fails (suitable for simple
  automated detection in submission/CI systems).

Major differences from the C implementation
- Strings are immutable in Java: functions return new `String` instances.
  In C, copy-returning functions allocate with `malloc` and require the caller
  to `free()` the result. In Java there is no manual free; the garbage collector
  reclaims memory when there are no references.
- The `lengthSplit` function returns a `List<String>` in Java. In C the
  equivalent returned a `char **` (array of C strings) and required explicit
  allocation and deallocation of each piece.
- Error handling: Java uses exceptions for invalid inputs (we throw
  `IllegalArgumentException` for `lengthSplit` when inputs are invalid). In C
  the function returned `NULL` or used other error conventions; see the C
  implementation for its contract.

STYLE and headers
- All new files I created include the repository's required header format
  (Name, Email, Date, Lab/Task, Description) in a doc-style block or top
  metadata block. See `STYLE.md` at the repository root for the canonical
  template and cross-language guidance.

Notes and next steps
- If you want automated JUnit tests instead of the visual tester, I can
  convert the test cases to JUnit and make the tester exit with non-zero
  status on failures.
- If the grader expects a different null/exception contract (for example,
  throwing NullPointerException instead of returning null), tell me and I
  will adjust the implementations quickly.
