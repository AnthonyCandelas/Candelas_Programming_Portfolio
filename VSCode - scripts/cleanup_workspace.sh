#!/usr/bin/env bash
# Workspace-wide housekeeping helper
# - safe by default; non-destructive
# - runs `make clean` in folders with a Makefile
# - removes common build artifacts (obj/, *.o, *.zip, common executables)
# - deletes .DS_Store files
# - for each git repo under the workspace shows a `git clean -fdn` dry-run; only runs destructive clean with --force-clean

set -euo pipefail

ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
cd "$ROOT_DIR"

echo "Workspace housekeeping (root: $ROOT_DIR)"

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
    if [ "${DRY_RUN-}" = "1" ]; then
      echo "   [dry-run] would remove: $f"
    else
      rm -rf -- "$f" || true
      echo "   removed: $f"
    fi
  fi
}

# Defaults
RECENT_DAYS=7
# safe-by-default: don't actually delete unless --apply is passed
DRY_RUN=1
# logging
LOG=0
LOG_DIR=".housekeeping"

# parse simple args: --recent N, --clear-ccache, --force-clean
while [ "$#" -gt 0 ]; do
  case "$1" in
    --recent)
      shift
      RECENT_DAYS=${1-}
      shift
      ;;
    --recent=*)
      RECENT_DAYS="${1#--recent=}"
      shift
      ;;
    --clear-ccache)
      CLEAR_CCACHE=1
      shift
      ;;
    --apply|--no-dry-run)
      DRY_RUN=0
      shift
      ;;
    --log)
      LOG=1
      shift
      ;;
    --force-clean)
      FORCE_CLEAN=1
      shift
      ;;
    *)
      echo "Unknown option: $1"
      shift
      ;;
  esac
done

if [ -z "${RECENT_DAYS-}" ]; then
  RECENT_DAYS=7
fi

# announce dry-run vs apply
if [ "${DRY_RUN-}" = "1" ]; then
  echo "Running in dry-run mode (no files will be deleted). To apply changes use --apply"
fi

echo "1) find recently active files and derive target scopes (recent: $RECENT_DAYS day(s))"
# Build a unique list of target directories (repo roots or parent dirs) based on recent file activity
TARGET_DIRS=()
add_target() {
  local cand="$1"
  for t in "${TARGET_DIRS[@]:-}"; do
    [ "$t" = "$cand" ] && return
  done
  TARGET_DIRS+=("$cand")
}
if [ "$RECENT_DAYS" -gt 0 ]; then
  # find files modified within RECENT_DAYS
  while IFS= read -r -d $'\0' f; do
    # walk up to find nearest .git; otherwise use the file's parent directory
    dir=$(dirname "$f")
    found=0
    while [ "$dir" != "$ROOT_DIR" ] && [ "$dir" != "/" ] && [ -n "$dir" ]; do
      if [ -d "$dir/.git" ]; then
        add_target "$dir"
        found=1
        break
      fi
      parent=$(dirname "$dir")
      if [ "$parent" = "$dir" ]; then break; fi
      dir="$parent"
    done
    if [ "$found" -eq 0 ]; then
      add_target "$(dirname "$f")"
    fi
  done < <(find . -type f -mtime -${RECENT_DAYS} -print0 || true)
fi

# fallback: if nothing matched (no recent activity), operate on the whole workspace
if [ "${#TARGET_DIRS[@]}" -eq 0 ]; then
  echo "No recently modified files found in the last $RECENT_DAYS day(s). Defaulting to full workspace scan."
  TARGET_DIRS=(.)
else
  echo "Operating on ${#TARGET_DIRS[@]} target(s) derived from recent activity"
fi

echo "Running make clean in the selected targets (if Makefile present)"
for dir in "${TARGET_DIRS[@]}"; do
  if [ -f "$dir/Makefile" ]; then
    echo "-> running make clean in $dir"
    (cd "$dir" && make clean) || echo "  make clean failed in $dir (continuing)"
  fi
done

echo "2) remove common artifacts in each target"
for tgt in "${TARGET_DIRS[@]}"; do
  echo "-> scanning $tgt"
  while IFS= read -r -d $'\0' f; do record_and_remove "$f"; done < <(find "$tgt" -type f -name '*.o' -print0 || true)
  while IFS= read -r -d $'\0' d; do record_and_remove "$d"; done < <(find "$tgt" -type d -name obj -print0 || true)
  while IFS= read -r -d $'\0' z; do record_and_remove "$z"; done < <(find "$tgt" -name '*.zip' -print0 || true)
  while IFS= read -r -d $'\0' ex; do record_and_remove "$ex"; done < <(find "$tgt" -type f \( -name horse -o -name test_game -o -name a.out \) -print0 || true)
done

echo "3) remove .DS_Store files (in each target)"
for tgt in "${TARGET_DIRS[@]}"; do
  while IFS= read -r -d $'\0' ds; do record_and_remove "$ds"; done < <(find "$tgt" -name '.DS_Store' -print0 || true)
done

echo "4) ccache (if installed)"
if command -v ccache >/dev/null 2>&1; then
  ccache -s || true
    if [ "${CLEAR_CCACHE-}" = "1" ]; then
    echo "Clearing ccache..."
    ccache -C || true
  else
    echo "To clear ccache, re-run with --clear-ccache"
  fi
else
  echo "ccache not found; skipping"
fi

echo "5) git repos: dry-run git clean for each selected repo-root"
for tgt in "${TARGET_DIRS[@]}"; do
  # if this target is a repo root, run git dry-run there; otherwise try to find a repo root inside
  if [ -d "$tgt/.git" ]; then
    repo_root="$tgt"
  else
    # find the nearest repo root under this target (if any)
    repo_root=""
    while IFS= read -r -d $'\0' g; do
      # take each .git directory and if it's under tgt, run on that repo
      droot=$(dirname "$g")
      echo "-> git dry-run in $droot"
      git -C "$droot" clean -fdn || true
      if [ "${FORCE_CLEAN-}" = "1" ]; then
        echo "  Running destructive clean in $droot"
        git -C "$droot" clean -fdx || true
      fi
    done < <(find "$tgt" -type d -name .git -print0 || true)
    continue
  fi
  echo "-> git dry-run in $repo_root"
  git -C "$repo_root" clean -fdn || true
  if [ "${FORCE_CLEAN-}" = "1" ]; then
    echo "  Running destructive clean in $repo_root"
    git -C "$repo_root" clean -fdx || true
  fi
done

echo
echo "Workspace housekeeping complete. Summary:"
if [ "${DRY_RUN-}" = "1" ]; then
  echo "  Mode: dry-run (no deletions were performed)"
else
  echo "  Mode: apply (deletions performed)"
fi
echo "  Items (or items that would be removed): $REMOVED_COUNT"
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
  echo "  Items list:"
  for p in "${REMOVED_PATHS[@]}"; do
    echo "   - $p"
  done
fi

if [ "$LOG" -eq 1 ]; then
  mkdir -p "$LOG_DIR" || true
  ts=$(date +"%Y%m%d_%H%M%S")
  logfile="$LOG_DIR/cleanup_$ts.log"
  {
    echo "Cleanup run: $(date -u)"
    echo "Root: $ROOT_DIR"
    echo "Mode: $( [ "$DRY_RUN" -eq 1 ] && echo "dry-run" || echo "apply")"
    echo "Recent-days: $RECENT_DAYS"
    echo "Items: $REMOVED_COUNT"
    echo "Bytes: $REMOVED_BYTES"
    echo "---"
    for p in "${REMOVED_PATHS[@]}"; do echo "$p"; done
  } > "$logfile"
  echo "Log written: $logfile"
fi

echo "Done."
