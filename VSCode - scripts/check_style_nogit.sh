#!/usr/bin/env bash
# Scan repository files (by extension) for the required header fields from STYLE.md
# This is a fallback scanner that does not require a git repository.

set -euo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$REPO_ROOT"

EXTENSIONS=("c" "h" "java" "md")
FAIL=0

echo "Scanning files under $REPO_ROOT for STYLE.md header fields..."

find . -type f \( -name "*.c" -o -name "*.h" -o -name "*.java" -o -name "*.md" \) -print | while IFS= read -r file; do
  # skip files in .git or .githooks
  case "$file" in
    ./.git/*|./.githooks/*)
      continue
      ;;
  esac

  # get the first 40 lines
  head_lines=$(head -n 40 "$file" 2>/dev/null || true)

  missing=()
  for field in "Name:" "Email:" "Date:" "Lab/Task:"; do
    if ! echo "$head_lines" | grep -q "${field}"; then
      missing+=("$field")
    fi
  done

  if [ ${#missing[@]} -ne 0 ]; then
    echo "MISSING: $file -> missing: ${missing[*]}"
    FAIL=1
  fi
done

if [ $FAIL -ne 0 ]; then
  echo "\nOne or more files are missing required header fields."
  exit 2
fi

echo "All scanned files include the required header fields." 
exit 0
