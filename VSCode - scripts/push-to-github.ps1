<#
.SYNOPSIS
  Stage, commit, and push changes to the configured origin remote.

USAGE
  ./scripts/push-to-github.ps1 -Message "Your commit message"
  ./scripts/push-to-github.ps1 -Message "WIP" -DryRun

PARAMETERS
  -Message  : Commit message (default: "Update")
  -DryRun   : Show the git commands that would be run, but don't execute them
  -NoPush   : Stage/commit but do not push
#>
param(
  [string]$Message = "Update",
  [switch]$DryRun,
  [switch]$NoPush
)

# Resolve repo root (script located in scripts/)
$scriptDir = Split-Path -Parent $MyInvocation.MyCommand.Definition
$repoRoot = Resolve-Path (Join-Path $scriptDir "..")
Set-Location $repoRoot

Write-Host "Repository root: $repoRoot"
Write-Host "Commit message: $Message"
if ($DryRun) { Write-Host "DRY-RUN: Commands will not be executed." }

$cmds = @(
  'git add -A',
  "git commit -m \"$Message\"",
  'git push'
)

if ($NoPush) {
  $cmds = $cmds[0..1]
}

if ($DryRun) {
  Write-Host "DRY-RUN: The following commands would be run:" -ForegroundColor Yellow
  $cmds | ForEach-Object { Write-Host "  $_" }
  exit 0
}

# Execute
foreach ($c in $cmds) {
  Write-Host "> $c"
  $proc = Start-Process -FilePath "git" -ArgumentList $c.Substring(4) -NoNewWindow -Wait -PassThru -RedirectStandardOutput stdout.txt -RedirectStandardError stderr.txt
  if ($proc.ExitCode -ne 0) {
    Write-Host "Command failed (exit code $($proc.ExitCode)): $c" -ForegroundColor Red
    Get-Content stderr.txt -Raw | Write-Host
    Remove-Item -Force stdout.txt, stderr.txt -ErrorAction SilentlyContinue
    exit $proc.ExitCode
  }
  Remove-Item -Force stdout.txt, stderr.txt -ErrorAction SilentlyContinue
}

Write-Host "Done." -ForegroundColor Green
