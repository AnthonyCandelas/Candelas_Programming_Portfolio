<#
.SYNOPSIS
  Windows-focused build script for Hack11. Attempts to find a usable
  compiler (gcc from MSYS2/MinGW, or clang), compiles and runs the tester,
  and appends all output to BUILD_LOG.txt.

USAGE
  .\build_windows.ps1        # compile and run
  .\build_windows.ps1 -Clean # clean build artifacts
#>

param(
  [switch]$Clean
)

Set-StrictMode -Version Latest
$ErrorActionPreference = 'Continue'

$root = Split-Path -Parent $MyInvocation.MyCommand.Definition
Set-Location $root
$log = Join-Path $root 'BUILD_LOG.txt'
function Log($m) { $ts = Get-Date -Format 'yyyy-MM-dd HH:mm:ss'; Add-Content $log "[$ts] $m" }

Log "=== build_windows.ps1 started ==="
Log "Working dir: $root"

if ($Clean) {
  Log "Cleaning artifacts"
  Remove-Item -Force .\airportTester.exe -ErrorAction SilentlyContinue
  Remove-Item -Force .\airportTester -ErrorAction SilentlyContinue
  Log "Clean complete"
  Log "=== build_windows.ps1 ended ==="
  exit 0
}

# Helper to try running a command and capture stdout+stderr
function Run-Capture($cmd, $args) {
  $stdout = New-TemporaryFile
  $stderr = New-TemporaryFile
  $proc = Start-Process -FilePath $cmd -ArgumentList $args -NoNewWindow -Wait -PassThru -RedirectStandardOutput $stdout -RedirectStandardError $stderr
  $out = Get-Content $stdout -Raw -ErrorAction SilentlyContinue
  $err = Get-Content $stderr -Raw -ErrorAction SilentlyContinue
  Remove-Item -Force $stdout, $stderr -ErrorAction SilentlyContinue
  return @{ ExitCode = $proc.ExitCode; StdOut = $out; StdErr = $err }
}

# 1) Look for gcc on PATH
$gccPath = $null
try { $whichGcc = & where.exe gcc 2>&1 | Out-String; if ($LASTEXITCODE -eq 0 -and $whichGcc.Trim() -ne '') { $gccPath = ($whichGcc -split "`r?`n")[0].Trim() } } catch {}
if ($gccPath) { Log "Found gcc on PATH: $gccPath" }

# 2) If not found, check common MSYS2 / MinGW paths
if (-not $gccPath) {
  $candidates = @(
    'C:\msys64\mingw64\bin\gcc.exe',
    'C:\msys64\mingw32\bin\gcc.exe',
    'C:\msys64\usr\bin\gcc.exe',
    'C:\Program Files\mingw-w64\mingw64\bin\gcc.exe',
    'C:\Program Files (x86)\mingw-w64\mingw32\bin\gcc.exe'
  )
  foreach ($p in $candidates) {
    if (Test-Path $p) { $gccPath = $p; Log "Found gcc at candidate: $p"; break }
  }
}

# 3) Look for clang
$clangPath = $null
try { $whichClang = & where.exe clang 2>&1 | Out-String; if ($LASTEXITCODE -eq 0 -and $whichClang.Trim() -ne '') { $clangPath = ($whichClang -split "`r?`n")[0].Trim() } } catch {}
if ($clangPath) { Log "Found clang on PATH: $clangPath" }

# 4) If no gcc/clang, try to locate cl (MSVC). Use where.exe and vswhere to find VS installs.
$clPath = $null
try { $whichCl = & where.exe cl 2>&1 | Out-String; if ($LASTEXITCODE -eq 0 -and $whichCl.Trim() -ne '') { $clPath = ($whichCl -split "`r?`n")[0].Trim(); Log "Found cl on PATH: $clPath" } } catch {}

if (-not ($gccPath -or $clangPath -or $clPath)) {
  Log "No C compiler found on PATH or common locations."
  Log "Please install one of the following and re-run this script:"
  Log " - MSYS2 (recommended on Windows) and install mingw-w64 toolchain (pacman -S mingw-w64-x86_64-gcc)"
  Log " - MinGW-w64 / WinLibs (add gcc to PATH)"
  Log " - Visual Studio (open Developer Command Prompt or ensure cl is on PATH)"
  Log "Refer to BUILD_INSTRUCTIONS.md for detailed steps."
  Log "=== build_windows.ps1 ended ==="
  Write-Host "No supported compilers found. See BUILD_LOG.txt for details." -ForegroundColor Yellow
  exit 1
}

# Prefer gcc if available
if ($gccPath) {
  Log "Compiling with gcc: $gccPath"
  $cmd = "$gccPath"
  $args = '-std=c11 -Wall -Wextra -o airportTester airport.c airportTester.c -lm'
  $res = Run-Capture $cmd $args
  Log "gcc exit: $($res.ExitCode)"
  Log "gcc stdout:\n$($res.StdOut)"
  Log "gcc stderr:\n$($res.StdErr)"
  if ($res.ExitCode -eq 0) {
    Log "gcc compile succeeded. Running .\airportTester"
    try { $run = & .\airportTester 2>&1 | Out-String; Log "airportTester output:\n$run" } catch { Log "Failed to run airportTester: $_" }
    Log "=== build_windows.ps1 ended ==="
    Write-Host "Build succeeded with gcc. See BUILD_LOG.txt for details." -ForegroundColor Green
    exit 0
  }
}

# Try clang
if ($clangPath) {
  Log "Compiling with clang: $clangPath"
  $cmd = "$clangPath"
  $args = '-std=c11 -Wall -Wextra -o airportTester airport.c airportTester.c -lm'
  $res = Run-Capture $cmd $args
  Log "clang exit: $($res.ExitCode)"
  Log "clang stdout:\n$($res.StdOut)"
  Log "clang stderr:\n$($res.StdErr)"
  if ($res.ExitCode -eq 0) {
    Log "clang compile succeeded. Running .\airportTester"
    try { $run = & .\airportTester 2>&1 | Out-String; Log "airportTester output:\n$run" } catch { Log "Failed to run airportTester: $_" }
    Log "=== build_windows.ps1 ended ==="
    Write-Host "Build succeeded with clang. See BUILD_LOG.txt for details." -ForegroundColor Green
    exit 0
  }
}

# Try cl if available on PATH (rare in PowerShell without Developer prompt)
if ($clPath) {
  Log "Attempting build with cl (MSVC) found at $clPath"
  # cl needs special flags and may require Developer environment; attempt basic compile
  $cmd = 'cmd.exe'
  $args = '/c cl /nologo /W3 /EHsc airport.c airportTester.c /link /OUT:airportTester.exe'
  $res = Run-Capture $cmd $args
  Log "cl exit: $($res.ExitCode)"
  Log "cl stdout:\n$($res.StdOut)"
  Log "cl stderr:\n$($res.StdErr)"
  if ($res.ExitCode -eq 0) {
    Log "cl compile succeeded. Running airportTester.exe"
    try { $run = & .\airportTester.exe 2>&1 | Out-String; Log "airportTester.exe output:\n$run" } catch { Log "Failed to run airportTester.exe: $_" }
    Log "=== build_windows.ps1 ended ==="
    Write-Host "Build succeeded with cl. See BUILD_LOG.txt for details." -ForegroundColor Green
    exit 0
  } else {
    Log "cl compile attempt failed. If you have Visual Studio installed, run this script inside a Developer Command Prompt to ensure environment variables are set."
  }
}

Log "All compile attempts failed. See earlier messages for details."
Log "=== build_windows.ps1 ended ==="
Write-Host "Build failed. See BUILD_LOG.txt for details." -ForegroundColor Red
exit 2
