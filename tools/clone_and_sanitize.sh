#!/usr/bin/env bash
# clone_and_sanitize.sh
# Clone a repository and run the sanitize script in one step.
# Usage: clone_and_sanitize.sh <repo-url> [target-dir] [--auto-replace] [--init-git <git-url>]

set -euo pipefail

if [ "$#" -lt 1 ]; then
  echo "Usage: $0 <repo-url> [target-dir] [--auto-replace] [--init-git <git-url>]"
  exit 2
fi

REPO_URL="$1"
DEST_ARG="${2:-}"
shift || true

AUTO_REPLACE=0
INIT_GIT_URL=""

# If second arg is an option (starts with --), leave DEST empty
if [[ "$DEST_ARG" =~ ^-- ]]; then
  # No explicit dest provided
  set -- "${DEST_ARG}" "$@"
  DEST_ARG=""i

while [ "$#" -gt 0 ]; do
  case "$1" in
    --auto-replace) AUTO_REPLACE=1; shift ;;
    --init-git) INIT_GIT_URL="$2"; shift 2 ;;
    *)
      if [ -z "$DEST_ARG" ]; then
        DEST_ARG="$1"
        shift
      else
        echo "Unknown option: $1"
        exit 2
      fi
      ;;
  esac
done

DEST_DIR="${DEST_ARG:-$(basename "$REPO_URL" .git)}"

echo "Cloning $REPO_URL -> $DEST_DIR"
if [ -d "$DEST_DIR" ]; then
  echo "Error: destination directory already exists: $DEST_DIR"
  exit 2
fi

git clone "$REPO_URL" "$DEST_DIR"

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
SANITIZE_SCRIPT="$SCRIPT_DIR/sanitize_cloned_repo.sh"

if [ ! -x "$SANITIZE_SCRIPT" ]; then
  echo "Sanitize script not found or not executable: $SANITIZE_SCRIPT"
  echo "Make sure tools/sanitize_cloned_repo.sh exists and is executable."
  exit 2
fi

SANITIZE_ARGS=()
if [ "$AUTO_REPLACE" -eq 1 ]; then
  SANITIZE_ARGS+=(--auto-replace)
fi
if [ -n "$INIT_GIT_URL" ]; then
  SANITIZE_ARGS+=(--init-git "$INIT_GIT_URL")
fi

# Run sanitizer on the newly cloned repo
"$SANITIZE_SCRIPT" "$DEST_DIR" "${SANITIZE_ARGS[@]}"

echo "Clone and sanitize complete for $DEST_DIR"

echo "Note: the folder '$DEST_DIR' is now sanitized (no .git)."
if [ -n "$INIT_GIT_URL" ]; then
  echo "A new git repo was initialized and origin set to $INIT_GIT_URL. Push when ready."
else
  echo "Initialize the folder as a git repo and set your origin if you want to push from it."
fi
