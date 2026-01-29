#!/usr/bin/env bash
# Housekeeping helper for the Lab09 workspace
# - non-destructive by default
# - performs: make clean, remove common artifacts, remove .DS_Store, remove obj/
# - shows a dry-run for destructive git clean and only runs it with --force

set -euo pipefail

HERE="$(cd "$(dirname "$0")/.." && pwd)"
cd "$HERE"

echo "Running housekeeping (non-destructive by default) in: $HERE"

# bookkeeping
declare -a REMOVED_PATHS=()
REMOVED_BYTES=0
REMOVED_COUNT=0

# portable size function (macOS and GNU stat)
get_size() {
  local file="$1"
  if [ -z "$file" ] || [ ! -e "$file" ]; then
    echo 0
    return
  fi
  if stat -f%z "$file" >/dev/null 2>&1; then
    stat -f%z "$file"
  else
    stat --printf=%s "$file" 2>/dev/null || echo 0
  fi
}

record_and_remove() {
  local f="$1"
  if [ -e "$f" ]; then
    local s=$(get_size "$f")
    REMOVED_BYTES=$((REMOVED_BYTES + s))
    REMOVED_COUNT=$((REMOVED_COUNT + 1))
    REMOVED_PATHS+=("$f")
    rm -rf -- "$f" || true
  fi
}

echo "1) make clean"
if command -v make >/dev/null 2>&1; then
  make clean || true
else
  echo "  make not found; skipping make clean"
fi

echo "2) remove common artifacts: zip, local execs, obj/"
record_and_remove "Lab09_gameFunctions_submission.zip"
record_and_remove "horse"
record_and_remove "test_game"
record_and_remove "obj"

echo "3) remove .DS_Store files"
while IFS= read -r -d $'\0' file; do
  record_and_remove "$file"
done < <(find . -name '.DS_Store' -print0 || true)

# ccache: clear if present
if command -v ccache >/dev/null 2>&1; then
  echo "4) ccache detected: showing stats"
  ccache -s || true
  if [ "${1-}" = "--clear-ccache" ] ; then
    echo "   clearing ccache..."
    ccache -C || true
    echo "   ccache cleared"
  else
    echo "   to clear ccache, run: $0 --clear-ccache"
  fi
else
  echo "4) ccache not installed; skipping"
fi

# Git destructive clean: dry-run by default
if [ "${1-}" = "--clean-untracked" ] || [ "${1-}" = "--force-clean" ]; then
  echo "5) git clean dry-run (untracked files and directories):"
  git clean -fdn || true
  if [ "${1-}" = "--force-clean" ]; then
    echo "   running destructive clean: git clean -fdx"
    git clean -fdx || true
  else
    echo "   to actually remove untracked files, run: $0 --force-clean"
  fi
else
  echo "5) git clean not requested. To see what would be removed run: $0 --clean-untracked"
fi

echo
echo "Housekeeping complete. Summary:"
echo "  Files removed: $REMOVED_COUNT"
human_readable() {
  awk 'function human(x){ split("B KB MB GB TB",u); for(i=1;x>=1024&&i<5;i++) x/=1024; printf("%.2f %s", x, u[i]) }{human($1)}' <<< "$1"
}
if [ "$REMOVED_BYTES" -gt 0 ]; then
  echo -n "  Total bytes freed: $REMOVED_BYTES bytes"
  echo " ($(human_readable $REMOVED_BYTES))"
else
  echo "  Total bytes freed: 0"
fi
if [ "$REMOVED_COUNT" -gt 0 ]; then
  echo "  Removed files (first 200 chars each):"
  for p in "${REMOVED_PATHS[@]}"; do
    echo "   - $p"
  done
fi

echo "Done."
