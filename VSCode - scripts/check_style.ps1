<#
.SYNOPSIS
  PowerShell port of scripts/check_style.sh

USAGE
  ./scripts/check_style.ps1            # checks staged files
  ./scripts/check_style.ps1 -All      # checks all tracked files

Description
  Verifies the first 40 lines of source files include the required
  header fields: Name:, Email:, Date:, Lab/Task:

  Checks files with extensions: .c, .h, .java, .md
#>
param(
  [switch]$All
)

Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'

# Resolve repo root (script placed in scripts/)
$scriptDir = Split-Path -Parent $MyInvocation.MyCommand.Definition
$repoRoot = Resolve-Path (Join-Path $scriptDir "..")
Push-Location $repoRoot

try {
  # gather files
  if ($All) {
    $raw = & git ls-files 2>$null
  } else {
    $raw = & git diff --cached --name-only --diff-filter=ACM 2>$null
  }
  $files = @()
  if ($raw) {
    $raw -split "`n" | ForEach-Object { $t = $_.Trim(); if ($t) { $files += $t } }
  }

  if ($files.Count -eq 0) {
    Write-Host "No files to check (staged files empty)." -ForegroundColor Yellow
    exit 0
  }

  Write-Host "Checking $($files.Count) file(s) for STYLE.md header..."

  $extPattern = '\.(c|h|java|md)$'
  $fail = $false

  foreach ($f in $files) {
    if (-not ($f -match $extPattern)) { continue }

    # prepare head lines
    $headLines = ""
    if ($All) {
      $path = Join-Path $repoRoot $f
      if (-not (Test-Path $path)) { continue }
      try { $headLines = Get-Content -Path $path -TotalCount 40 -ErrorAction Stop -Raw } catch { $headLines = "" }
    } else {
      # try to read staged content via git show
      try {
        $show = & git show ":$f" 2>$null
        if ($LASTEXITCODE -eq 0 -and $show) {
          $headLines = ($show -split "`n")[0..([Math]::Min(39, ($show -split "`n").Count - 1))] -join "`n"
        } else {
          $path = Join-Path $repoRoot $f
          if (Test-Path $path) { $headLines = Get-Content -Path $path -TotalCount 40 -ErrorAction SilentlyContinue -Raw }
        }
      } catch {
        $path = Join-Path $repoRoot $f
        if (Test-Path $path) { $headLines = Get-Content -Path $path -TotalCount 40 -ErrorAction SilentlyContinue -Raw }
      }
    }

    if (-not $headLines) { continue }

    foreach ($field in @('Name:','Email:','Date:','Lab/Task:')) {
      if (-not ($headLines -like "*${field}*")) {
        Write-Host "STYLE ERROR: $f missing required header field: ${field}" -ForegroundColor Red
        Write-Host "--- file head ---"
        $headLines -split "`n" | Select-Object -First 40 | ForEach-Object { Write-Host $_ }
        Write-Host "--- end head ---"
        $fail = $true
        break
      }
    }
  }

  if ($fail) {
    Write-Host "`nOne or more files failed the STYLE.md header check. Please add the required header per STYLE.md." -ForegroundColor Red
    exit 2
  }

  Write-Host "All checked files include the required header fields." -ForegroundColor Green
  exit 0
} finally {
  Pop-Location
}
