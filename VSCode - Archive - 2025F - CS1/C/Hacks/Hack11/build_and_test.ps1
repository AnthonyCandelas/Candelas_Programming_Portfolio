<#
.SYNOPSIS
  Attempts to detect available C compilers (gcc, clang, cl) on Windows
  and compile/run the Hack11 tester. Records all output to BUILD_LOG.txt

USAGE
  .\build_and_test.ps1

This script is safe to run and only compiles files in the Hack11 folder.
It does not modify system settings. It will append diagnostic and build
output to `BUILD_LOG.txt` in the same folder.
#>

Set-StrictMode -Version Latest
$ErrorActionPreference = 'Continue'

$root = Split-Path -Parent $MyInvocation.MyCommand.Definition
Set-Location $root
$log = Join-Path $root 'BUILD_LOG.txt'

function Log($msg) { $ts = Get-Date -Format "yyyy-MM-dd HH:mm:ss"; Add-Content -Path $log -Value ("[$ts] $msg") }

Log "=== Build-and-test started ==="
Log "Working dir: $root"

# Record header contents
$files = Get-ChildItem -Path $root -Filter '*.c' -Name | Sort-Object
Log "Source files: $($files -join ', ')"

# check compilers
$compilers = @('gcc','clang','cl')
$found = @()
foreach ($c in $compilers) {
  try {
    $out = & $c --version 2>&1 | Out-String
    Log "Compiler check: $c found"
    Log "$out"
    $found += $c
  } catch {
    # For 'cl' (MSVC) --version is not used; check via where
    if ($c -eq 'cl') {
      $which = & where.exe cl 2>&1 | Out-String
      if ($LASTEXITCODE -eq 0 -and $which.Trim() -ne '') {
        Log "Compiler check: cl found at: $which"
        $found += 'cl'
      } else {
        Log "Compiler check: cl not found"
      }
    } else {
      Log "Compiler check: $c not found or not on PATH"
    }
  }
}

if ($found.Count -eq 0) {
  Log "No supported compilers found on PATH. Aborting compile attempts."
  Log "See BUILD_INSTRUCTIONS.md for how to install a toolchain (MinGW/msys2, WSL, or Visual Studio)."
  Log "=== Build-and-test ended ==="
  exit 0
}

# Try gcc first if present
if ($found -contains 'gcc') {
  Log "Attempting to compile with gcc..."
  $cmd = 'gcc -std=c11 -Wall -Wextra -o airportTester airport.c airportTester.c -lm'
  Log "Command: $cmd"
  $proc = Start-Process -FilePath 'cmd.exe' -ArgumentList "/c $cmd" -NoNewWindow -Wait -PassThru -RedirectStandardOutput temp_stdout.txt -RedirectStandardError temp_stderr.txt
  $stdout = Get-Content temp_stdout.txt -Raw -ErrorAction SilentlyContinue
  $stderr = Get-Content temp_stderr.txt -Raw -ErrorAction SilentlyContinue
  Log "gcc stdout:\n$stdout"
  Log "gcc stderr:\n$stderr"
  Remove-Item -Force temp_stdout.txt, temp_stderr.txt -ErrorAction SilentlyContinue
  if ($proc.ExitCode -eq 0) {
    Log "gcc compile succeeded. Running ./airportTester"
    try {
      $runout = & .\airportTester 2>&1 | Out-String
      Log "airportTester output:\n$runout"
    } catch {
      Log "Failed to run airportTester after successful gcc compile: $_"
    }
  } else {
    Log "gcc compile failed with exit code $($proc.ExitCode)"
  }
}

# Try clang if present
if ($found -contains 'clang') {
  Log "Attempting to compile with clang..."
  $cmd = 'clang -std=c11 -Wall -Wextra -o airportTester airport.c airportTester.c -lm'
  Log "Command: $cmd"
  $proc = Start-Process -FilePath 'cmd.exe' -ArgumentList "/c $cmd" -NoNewWindow -Wait -PassThru -RedirectStandardOutput temp_stdout.txt -RedirectStandardError temp_stderr.txt
  $stdout = Get-Content temp_stdout.txt -Raw -ErrorAction SilentlyContinue
  $stderr = Get-Content temp_stderr.txt -Raw -ErrorAction SilentlyContinue
  Log "clang stdout:\n$stdout"
  Log "clang stderr:\n$stderr"
  Remove-Item -Force temp_stdout.txt, temp_stderr.txt -ErrorAction SilentlyContinue
  if ($proc.ExitCode -eq 0) {
    Log "clang compile succeeded. Running ./airportTester"
    try {
      $runout = & .\airportTester 2>&1 | Out-String
      Log "airportTester output:\n$runout"
    } catch {
      Log "Failed to run airportTester after successful clang compile: $_"
    }
  } else {
    Log "clang compile failed with exit code $($proc.ExitCode)"
  }
}

# Try MSVC cl if present
if ($found -contains 'cl') {
  Log "Attempting to compile with MSVC (cl)..."
  # cl needs to be run in a developer command prompt; running from regular PowerShell may fail if environment not set.
  # Try a straightforward invocation and capture output
  $cmd = 'cl /nologo /W3 /EHsc airport.c airportTester.c /link /OUT:airportTester.exe'
  Log "Command: $cmd"
  $proc = Start-Process -FilePath 'cmd.exe' -ArgumentList "/c $cmd" -NoNewWindow -Wait -PassThru -RedirectStandardOutput temp_stdout.txt -RedirectStandardError temp_stderr.txt
  $stdout = Get-Content temp_stdout.txt -Raw -ErrorAction SilentlyContinue
  $stderr = Get-Content temp_stderr.txt -Raw -ErrorAction SilentlyContinue
  Log "cl stdout:\n$stdout"
  Log "cl stderr:\n$stderr"
  Remove-Item -Force temp_stdout.txt, temp_stderr.txt -ErrorAction SilentlyContinue
  if ($proc.ExitCode -eq 0) {
    Log "cl compile succeeded. Running airportTester.exe"
    try {
      $runout = & .\airportTester.exe 2>&1 | Out-String
      Log "airportTester.exe output:\n$runout"
    } catch {
      Log "Failed to run airportTester.exe after cl compile: $_"
    }
  } else {
    Log "cl compile failed with exit code $($proc.ExitCode)"
    Log "Note: cl typically requires a Developer Command Prompt with environment variables set."
  }
}

Log "=== Build-and-test ended ==="
Write-Host "Build-and-test finished. See BUILD_LOG.txt for details."
