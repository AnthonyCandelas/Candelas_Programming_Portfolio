````markdown
# Workspace Housekeeping

This workspace includes lightweight housekeeping helpers to safely remove common build artifacts and keep the tree tidy.

Files of interest
- `scripts/cleanup_workspace.sh` — workspace-wide helper. Key features:
  - safe by default; non-destructive for git-clean unless `--force-clean` is used
  - runs `make clean` in repositories that appear recently active (default: last 7 days)
  - removes common artifacts (`*.o`, `obj/`, `*.zip`, common executables) only in recently active areas
  - removes macOS `.DS_Store` files only in recently active areas
  - reports a concise summary at the end (files removed, total bytes freed, list of removed items)
  - supports `--recent N` to change the recent threshold in days, `--clear-ccache`, and `--force-clean`

Why this exists
- Running housekeeping across a large workspace can be slow and intrusive. The default mode focuses activity on files and folders that have been touched recently (by default: last 7 days). This reduces runtime and avoids surprising operations in long-idle projects.

Usage examples

```bash
# dry-run (default): only operate on items in repositories/dirs with activity in the last 7 days
./scripts/cleanup_workspace.sh

# target a different recent window (e.g. 14 days)
./scripts/cleanup_workspace.sh --recent 14

# dry-run is default. To actually delete artifacts use --apply
./scripts/cleanup_workspace.sh --apply

# write a timestamped log of what was (or would be) removed
./scripts/cleanup_workspace.sh --log

# clear ccache (if installed) while running
./scripts/cleanup_workspace.sh --clear-ccache

# DESTRUCTIVE: run git clean -fdx in active repos (use with caution)
./scripts/cleanup_workspace.sh --force-clean
```

Notes and safety
- The script is conservative by default: it finds recently modified files and restricts `make clean` / artifact removal to the directories that contain them. If a directory is inactive (no modifications in the recent window), the script will skip heavy operations there.
- `--force-clean` runs `git clean -fdx` in discovered git repositories — this is destructive and will delete untracked files. Only run if you are sure.
- If you prefer a fully global cleanup, run the script with `--recent 0` to disable the recent filter (advanced use).

If you want a log of what was removed, re-run with `--recent N --log` (I can add a `--log` flag if you want timestamps saved automatically).

````
