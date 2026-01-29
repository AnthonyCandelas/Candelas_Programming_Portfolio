#!/usr/bin/env bash
# Lightweight style checker that verifies required header metadata per STYLE.md

set -euo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

usage() {
  cat <<EOF
Usage: $0 [--all]
  --all    Check all tracked files in the repo. Otherwise checks staged files only.
EOF
  exit 1
}

CHECK_ALL=0
if [ "${1-}" = "--all" ]; then
  CHECK_ALL=1
fi

# File extensions to check
EXT_PATTERN='\.(c|h|java|md)$'

fail=0
files=()
if [ $CHECK_ALL -eq 1 ]; then
  # all tracked files
  while IFS= read -r f; do files+=("$f"); done < <(git ls-files)
else
  # staged files (added, copied, modified)
  while IFS= read -r f; do files+=("$f"); done < <(git diff --cached --name-only --diff-filter=ACM || true)
fi

if [ ${#files[@]} -eq 0 ]; then
  echo "No files to check (staged files empty)."
  exit 0
fi

echo "Checking ${#files[@]} file(s) for STYLE.md header..."

for f in "${files[@]}"; do
  # skip files that don't match extensions
  if ! [[ "$f" =~ $EXT_PATTERN ]]; then
    continue
  fi

  # get file contents: if checking staged files, try to read staged content
  if [ $CHECK_ALL -eq 1 ]; then
    content_file="$REPO_ROOT/$f"
    if [ ! -f "$content_file" ]; then
      # skip deleted/absent files
      continue
    fi
    head_lines=$(head -n 40 "$content_file" || true)
  else
    # try to read staged version if available
    if git show ":$f" >/dev/null 2>&1; then
      head_lines=$(git show ":$f" | head -n 40 || true)
    else
      # fallback to working tree copy
      if [ -f "$REPO_ROOT/$f" ]; then
        head_lines=$(head -n 40 "$REPO_ROOT/$f" || true)
      else
        continue
      fi
    fi
  fi

  # check for required metadata fields in the first 40 lines
  for field in "Name:" "Email:" "Date:" "Lab/Task:"; do
    if ! echo "$head_lines" | grep -q "${field}"; then
      echo "STYLE ERROR: $f missing required header field: ${field}"
      echo "--- file head ---"
      echo "$head_lines" | sed -n '1,40p'
      echo "--- end head ---"
      fail=1
      break
    fi
  done

done

if [ $fail -ne 0 ]; then
  echo "\nOne or more files failed the STYLE.md header check. Please add the required header per STYLE.md."
  exit 2
fi

echo "All checked files include the required header fields."
exit 0
