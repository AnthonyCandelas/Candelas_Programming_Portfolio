#!/usr/bin/env bash
# Simple helper: stage all, commit with message, then push to origin
# Usage: ./scripts/push-to-github.sh "Commit message"
# Options: --dry-run (print commands), --no-push (skip push)

set -euo pipefail

MSG="${1-Update}"
DRY_RUN=0
NO_PUSH=0
shift 1 2>/dev/null || true
for arg in "$@"; do
  case "$arg" in
    --dry-run) DRY_RUN=1; shift ;;
    --no-push) NO_PUSH=1; shift ;;
  esac
done

cmds=( "git add -A" "git commit -m \"$MSG\"" "git push" )
if [ "$NO_PUSH" -eq 1 ]; then
  cmds=( "git add -A" "git commit -m \"$MSG\"" )
fi

if [ "$DRY_RUN" -eq 1 ]; then
  echo "DRY-RUN: would run:"; for c in "${cmds[@]}"; do echo "  $c"; done; exit 0
fi

for c in "${cmds[@]}"; do
  echo "> $c"
  eval "$c"
done

echo "Done."
