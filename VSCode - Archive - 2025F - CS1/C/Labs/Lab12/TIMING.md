# Lab12 — Build & Timing Notes

This file contains quick commands you can use to build the Lab12 programs and measure execution time. Timing and instrumentation were intentionally removed from the source files to keep the submitted code minimal and free of unused variables.

POSIX (Linux, macOS, WSL)
```bash
cd C/Labs/Lab12
make            # builds jacobsthal, jacobsthalMemoization, palindrome
./jacobsthal 16 # naive; use small n only
./jacobsthalMemoization 64 # memoized, use large n

# wall-clock timing (if `time` is available)
/usr/bin/time -p ./jacobsthalMemoization 64
```

Windows PowerShell (with MinGW installed)
```powershell
# compile (if you don't use make)
C:/path/to/mingw64/bin/gcc.exe -std=c11 -Wall -Wextra -O2 -o jacobsthalMemoization jacobsthalMemoization.c
# measure runtime (PowerShell)
Measure-Command { .\jacobsthalMemoization 64 }
```

If you want instrumentation that counts recursive calls (to demonstrate the benefit of memoization), I can add an optional build target that compiles instrumented versions of the programs and produces a `BUILD_LOG.txt` showing call counts and timing. Ask me to add that if you want to include the numbers in lab notes or a writeup.