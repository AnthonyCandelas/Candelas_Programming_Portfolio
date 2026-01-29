<#
.SYNOPSIS
  Run a repository shell script inside WSL (if available).

USAGE
  .\scripts\run-in-wsl.ps1 ./scripts/check_style.sh --all
  .\scripts\run-in-wsl.ps1 ./scripts/cleanup_workspace.sh --apply

DESCRIPTION
  If WSL is installed this script will invoke `wsl bash -lc "<script> <args>"` so
  repository `.sh` helpers run in a Linux environment from PowerShell.

  If WSL is not installed the script prints concise install instructions and a link.
#>
param(
  [Parameter(Mandatory=$true, Position=0)]
  [string]$ScriptPath,
  [Parameter(Position=1, ValueFromRemainingArguments=$true)]
  [string[]]$Args
)

function Show-InstallHelp {
  Write-Host "WSL is not installed on this machine." -ForegroundColor Yellow
  Write-Host "To install WSL (recommended) run in an elevated PowerShell:" -ForegroundColor Yellow
  Write-Host "  wsl --install" -ForegroundColor Cyan
  Write-Host "After install restart, then run `wsl` to finish distro setup (e.g. Ubuntu)." -ForegroundColor Yellow
  Write-Host "More: https://aka.ms/wslinstall" -ForegroundColor Cyan
}

# Resolve the script path relative to repo root if needed
$scriptFull = Resolve-Path -LiteralPath $ScriptPath -ErrorAction SilentlyContinue
if (-not $scriptFull) {
  # try relative to repo root (assume script is in scripts/)
  $scriptDir = Split-Path -Parent $MyInvocation.MyCommand.Definition
  $repoRoot = Resolve-Path (Join-Path $scriptDir "..")
  $candidate = Join-Path $repoRoot $ScriptPath
  $scriptFull = Resolve-Path -LiteralPath $candidate -ErrorAction SilentlyContinue
  if (-not $scriptFull) {
    Write-Host "Cannot resolve script path: $ScriptPath" -ForegroundColor Red
    exit 2
  }
}

# Check WSL availability
$wslStatus = & wsl --status 2>&1 | Out-String
if ($LASTEXITCODE -ne 0 -or $wslStatus -match "not installed") {
  Show-InstallHelp
  exit 3
}

# Prepare command to run under WSL. Convert Windows path to WSL path using wslpath
$winPath = $scriptFull.Path
$wslPathProc = & wsl wslpath -a -u "${winPath}" 2>&1
if ($LASTEXITCODE -ne 0) {
  Write-Host "Failed to convert path to WSL path: $wslPathProc" -ForegroundColor Red
  exit 4
}
$wslPath = $wslPathProc.Trim()
$joinedArgs = $Args -join ' '
$cmd = "bash -lc '" + ($wslPath -replace "'","'\''") + (if ($joinedArgs) { " $joinedArgs" } else { "" }) + "'"

Write-Host "Running under WSL: $cmd"
# Run via wsl
$invoke = & wsl $cmd
$exit = $LASTEXITCODE
exit $exit
