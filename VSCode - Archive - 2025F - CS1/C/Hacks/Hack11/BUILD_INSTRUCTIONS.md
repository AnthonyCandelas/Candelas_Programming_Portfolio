# Build Instructions — Hack11 (C)

<!--
Name: Anthony Candelas
Email: tsallinger2@unl.edu
Date: 18NOV2025
Lab/Task: Hack11 - Build Instructions

Description:
This document describes how to build and run the `airportTester` program for Hack11 on Windows and POSIX systems.

NOTE: Instructions assume a local MinGW toolchain is present under the repository at `mingw64/` or that `gcc` is on the PATH.
-->

This document describes how to build and run the `airportTester` program for Hack11 on Windows and POSIX systems. The repository includes helper scripts:

- `build_and_test.ps1` — PowerShell script that attempts to detect compilers and build the tester, recording all output to `BUILD_LOG.txt`.
- `build_windows.ps1` — Windows-native PowerShell build script that attempts to locate a compiler (MinGW/MSYS2 gcc, clang, or MSVC `cl`), compile the tester, and record output in `BUILD_LOG.txt`.
- `Makefile.posix` — POSIX Makefile for use under WSL, macOS, or Linux.

Common build targets

POSIX (WSL, macOS, Linux):

```bash
# from C/Hacks/Hack11
make
./airportTester
```

Windows (with MinGW / mingw-w64 / MSYS2 / Git Bash):

Use the Windows build script which will try to detect a compiler and run the tests, recording output to `BUILD_LOG.txt`:

```powershell
# from C/Hacks/Hack11
.\build_windows.ps1

# to clean artifacts
.\build_windows.ps1 -Clean
```

Alternatively, if you have `gcc` on PATH you can compile directly:

```powershell
gcc -std=c11 -Wall -Wextra -o airportTester airport.c airportTester.c -lm
.\airportTester
```

Windows (Visual Studio cl.exe):

- Open "Developer Command Prompt for VS" (ensures `cl` is on PATH and environment is correct)
- Run:
```
cl /nologo /W3 /EHsc airport.c airportTester.c /link /OUT:airportTester.exe
airportTester.exe
```

If you do not have a compiler installed

- Option 1 (recommended): Install WSL and use GCC inside the Linux environment:
  - Run in an elevated PowerShell: `wsl --install` (requires Windows features/virtualization).
  - Open WSL, install build-essential: `sudo apt update && sudo apt install -y build-essential`
  - Build with `make` as shown above.

- Option 2: Install MinGW-w64 or MSYS2 and add `gcc` to PATH.
  - MSYS2: https://www.msys2.org/ (recommended on Windows)
  - MinGW-w64: https://winlibs.com/ or through pacman in MSYS2

- Option 3: Install Visual Studio (Community) and use its Developer Command Prompt.

Logging and diagnostics

- Use `build_and_test.ps1` (PowerShell) to automatically detect compilers and record outputs in `BUILD_LOG.txt`. Run it from `C/Hacks/Hack11`:

```powershell
.\build_and_test.ps1
# After it finishes, open BUILD_LOG.txt to review diagnostics
Get-Content BUILD_LOG.txt
```

If you want me to run compilation attempts on your behalf, tell me which toolchain to use (WSL/gcc, MinGW/gcc, or Visual Studio `cl`) and whether your terminal is running elevated (needed for WSL install or some system-level changes). I can then run the scripted attempts and capture results.
