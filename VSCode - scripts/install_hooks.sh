#!/usr/bin/env bash
# Installs the local .githooks directory as the repo hooks path and makes helper scripts executable.

set -euo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
GITHOOKS_DIR="$REPO_ROOT/.githooks"

if [ ! -d "$GITHOOKS_DIR" ]; then
  echo "No .githooks directory found; aborting."
  exit 1
fi

git config core.hooksPath .githooks
chmod +x "$GITHOOKS_DIR"/* || true
chmod +x "$REPO_ROOT/scripts"/*.sh || true

echo "Installed .githooks as core.hooksPath and made scripts executable."
echo "To uninstall: git config --unset core.hooksPath"
