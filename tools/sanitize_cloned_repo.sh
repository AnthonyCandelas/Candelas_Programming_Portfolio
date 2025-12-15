#!/usr/bin/env bash
# sanitize_cloned_repo.sh
# Remove .git from a cloned repo and optionally scrub instructor links.
# Usage: sanitize_cloned_repo.sh <path> [--auto-replace] [--init-git <your-git-url>]

set -euo pipefail

if [ "$#" -lt 1 ]; then
  echo "Usage: $0 <path-to-cloned-repo> [--auto-replace] [--init-git <git-url>]"
  exit 2
fi

TARGET="$1"
AUTO_REPLACE=0
INIT_GIT_URL=""
shift
while [ "$#" -gt 0 ]; do
  case "$1" in
    --auto-replace) AUTO_REPLACE=1; shift ;;
    --init-git) INIT_GIT_URL="$2"; shift 2 ;;
    *) echo "Unknown option: $1"; exit 2 ;;
  esac
done

if [ ! -d "$TARGET" ]; then
  echo "Error: path not found: $TARGET"
  exit 2
fi

# Resolve absolute path
TARGET_ABS=$(cd "$TARGET" && pwd)

echo "Sanitizing: $TARGET_ABS"

# 1) Remove .git directory if present
if [ -d "$TARGET_ABS/.git" ]; then
  echo "- Removing .git directory..."
  rm -rf "$TARGET_ABS/.git"
else
  echo "- No .git directory found (already sanitized or not a clone)."
fi

# 2) Find and optionally replace known instructor patterns
# Patterns to detect (add more as needed)
PATTERNS=(
  "github.com/cbourke/CSCE155-C-Lab13"
  "github.com/cbourke/CSCE155-C-Lab11"
  "cse.unl.edu/~cbourke"
  "https://github.com/cbourke"
)

MATCHES=0
for pat in "${PATTERNS[@]}"; do
  # Use grep to find matches in text files under the target
  while IFS= read -r -d $'\0' file; do
    if grep -Iq -- "$pat" "$file" 2>/dev/null; then
      MATCHES=$((MATCHES+1))
      echo "- Found pattern '$pat' in: $file"
      if [ $AUTO_REPLACE -eq 1 ]; then
        # Replace the exact pattern with a placeholder
        perl -pi -e "s|$pat|<INSTRUCTOR_LINK_REMOVED>|g" "$file"
        echo "  -> Replaced occurrences in $file"
      fi
    fi
  done < <(grep -Irl --exclude-dir=.git --exclude-dir=node_modules --exclude=*.png --exclude=*.jpg --exclude=*.pdf --exclude=*.o --exclude=*.exe -- "$pat" "$TARGET_ABS" 2>/dev/null || true)
done

if [ $MATCHES -eq 0 ]; then
  echo "- No instructor link patterns detected."
fi

# 3) Optionally initialize a new git repo and add your origin
if [ -n "$INIT_GIT_URL" ]; then
  echo "- Initializing new git repo and setting origin to: $INIT_GIT_URL"
  git -C "$TARGET_ABS" init
  git -C "$TARGET_ABS" add .
  git -C "$TARGET_ABS" commit -m "chore(sanitize): initialize repository after sanitizing external clone"
  git -C "$TARGET_ABS" remote add origin "$INIT_GIT_URL"
  echo "  -> New repo initialized. Push to your remote when ready."
else
  echo "- Not initializing a new git repo (no --init-git provided)."
fi

echo "Sanitization complete. Review files if --auto-replace was used."
