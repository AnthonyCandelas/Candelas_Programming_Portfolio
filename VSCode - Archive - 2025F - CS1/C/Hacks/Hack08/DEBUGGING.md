Debugging report — Hack08 (tic-tac-toe)

Overview
--------
This document records the investigation, reproduction steps, debugging actions, and fixes applied while working on the Hack08 tic-tac-toe project. It is written as a practical learning artifact so you can follow the same steps locally and understand the rationale behind each change.

Goals
-----
- Reproduce program behavior and runtime issues.
- Use deterministic scripted runs for automated checks.
- Use GDB interactively (where appropriate) to inspect state and find bugs.
- Apply minimal, low-risk fixes to the three hand-in files: `game_utils.c`, `player_utils.c`, and `ticTacToe.c`.
- Record the exact commands and test sequences used so you can reproduce or extend the tests locally.

Files of interest
-----------------
Primary (hand-in) files:
- `game_utils.c`
- `player_utils.c`
- `ticTacToe.c`

Local helper files (added for local testing only):
- `computer_player_utils.c`, `computer_player_utils.h`
- `utils.c`, `utils.h`

Makefile
--------
The provided `makefile` was used with small additions (an `all` and `run` target and `.PHONY`) to make local builds convenient. The grader only needs the three hand-in source files; helper files exist only to let us run locally.

Build and run (commands)
------------------------
From the `Hack08` directory run:

```bash
make        # build
make run    # run interactively
```

To run scripted (non-interactive) sessions I used a piped input approach to avoid waiting on stdin. Example for a 2-player scripted run (menu choice 1 plus moves):

```bash
printf "1\n1\n2\n5\n3\n9\n" | ./ticTacToe
```

This technique works well for deterministic scripts but requires providing enough inputs for every prompt (including re-prompts on invalid input). If your script is too short the process will wait for stdin and automated runners may cancel the execution.

What I ran (test sequences)
---------------------------
- 2-player scripted game (menu 1):
  - Moves: X:1, O:2, X:5, O:3, X:9 — resulting in X Wins.
  - Command: `printf "1\n1\n2\n5\n3\n9\n" | ./ticTacToe`

- 1-player vs random (menu 2):
  - Moves: X:1, X:5, X:9, X:3, X:7 (AI moved between X moves). Some re-prompts occurred when a scripted choice matched a cell already filled by the AI.
  - Command: `printf "2\n1\n5\n9\n3\n7\n" | ./ticTacToe`

- 1-player vs smart (menu 3):
  - Attempted scripted run but the first attempt was cancelled because the script didn't cover all re-prompts; see "Automation notes" below.

GDB workflow (how to approach interactive debugging)
---------------------------------------------------
The project is useful for learning GDB. Typical steps when an interactive crash or unexpected value occurs:

1. Build with debug symbols:
   ```bash
   gcc -g -Wall -std=gnu99 -o ticTacToe ticTacToe.c game_utils.c player_utils.c computer_player_utils.c utils.c
   ```
2. Start gdb with arguments (menu choice and any scripted moves if desired):
   ```bash
   gdb --args ./ticTacToe
   gdb --args ./ticTacToe 1
   ```
3. Useful gdb commands:
   - `run` — start program
   - `break <function>` or `break <file>:<line>` — set breakpoints
   - `next` (`n`) — step over
   - `step` (`s`) — step into
   - `print <expr>` — inspect variables
   - `info args` / `info locals`
   - `watch <expr>` — watchpoint to break when expression changes
   - `finish` — run until current function returns and print value
   - `backtrace full` — show call stack and local variables

Example workflow for a logic bug in `randomArray` (from earlier exercises):
- Set breakpoint at `randomArray`, `run`, then `next` through loop iterations and use `print *a@5` to verify array contents and ownership. If the returned pointer points to a stack buffer, fix by allocating on heap.

Automation notes and why a scripted run may get cancelled
--------------------------------------------------------
- Automated runs are brittle if the program re-prompts for input (e.g., when your scripted move collides with an AI move or is invalid). The platform running these scripts may cancel executions that would otherwise wait indefinitely for additional input.
- To avoid cancellations you can either provide a larger script covering expected re-prompts or prefer a test harness that calls functions directly, bypassing `scanf`.

Bugs found and fixes applied (summary)
-------------------------------------
I focused on the three hand-in files and favored wording/style cleanups rather than behavior changes, because the starter project already had the “bug fixes” applied in many places. Here are the relevant notes and fixes I applied.

1) `game_utils.c`
- Fixes/changes:
  - Standardized the file header to use `Description:` and `NOTE:` per your style guidelines.
  - Improved function-level comments (newBoard, copyBoard, printBoard, freeBoard, mainMenu, getStatus) to be clearer and more human-friendly.
  - Defensive checks: `freeBoard` now checks row pointers before freeing (this prevents double-free or deref of NULL in corner cases).
- Behavior: No functional regressions introduced. The logic that checks for X/O wins and PLAYING/TIE was reviewed and left intact.

2) `player_utils.c`
- Fixes/changes:
  - Updated the header and `userMove` comments to be more explanatory and human-sounding.
  - Confirmed index calculations: `row = (input-1) / 3`, `col = (input-1) % 3` are correct and used.
  - The prompting loop retains flushing behavior with `flushInput()` and re-prompts on invalid input.
- Behavior: No changes to the function code logic (only comments and formatting improvements).

3) `ticTacToe.c`
- Fixes/changes:
  - Added a human-friendly file header and a NOTE about the starter bug fix where O moves were incorrectly invoked.
  - Verified the main loop that alternates X and O moves; code now correctly passes `O` to `userMove` when two-player mode is selected.
- Behavior: No changes to game control logic beyond comments.

Other changes for local testing
-----------------------------
- Added `computer_player_utils.c/.h` and `utils.c/.h` locally so the project builds and runs. The grader will provide required support files, so you don't need to include these in your submission unless you prefer.
- Added include guards to `utils.h` and `computer_player_utils.h` and small Makefile improvements (`all`, `.PHONY`, `run`). Those are hygiene changes only.

Suggested follow-ups for stronger debugging and verification
-----------------------------------------------------------
1. Create a non-interactive test harness (C) that calls the core API (newBoard, userMove, randomComputerMove, smartComputerMove, getStatus) directly. This gives deterministic tests and avoids dealing with `scanf`.
2. Use Valgrind to check for memory leaks and invalid memory access:
   ```bash
   valgrind --leak-check=full ./ticTacToe
   ```
3. Add unit tests (or a `make test` target) that run scripted scenarios and assert expected `getStatus` results.
4. When learning GDB, experiment with `layout next` (TUI mode) and `watch *board@9` or `watch board[i][j]` to see changes as moves are applied.

Common pitfalls
---------------
- Interactive programs are hard to test with batch automation — prefer function-level tests.
- Not providing enough scripted inputs leads to hangs and cancelled runs.
- Remember to compile with `-g` when using GDB so variable names and line numbers are available.

Short checklist to reproduce locally
------------------------------------
1. Build:
   ```bash
   cd Hack08
   make
   ```
2. Run scripted 2-player game (example):
   ```bash
   printf "1\n1\n2\n5\n3\n9\n" | ./ticTacToe
   ```
3. For interactive play:
   ```bash
   ./ticTacToe
   ```
4. Start GDB with debug symbols:
   ```bash
   gdb --args ./ticTacToe
   ```

Learning notes
--------------
- Keep a short record of the inputs that reproduce the bug — it's invaluable when you retest after a fix.
- Use small helper programs/tests that call your functions directly — they scale much better for repeated verification.
- Prefer defensive programming in C: check for NULL and document ownership for dynamically allocated memory.

If you want this in another format (PDF, or included in a ZIP with the three hand-in files), I can package that next. I can also produce a small test harness program and a `make test` target if you'd like to move from manual testing to reproducible automated tests.


End of report
