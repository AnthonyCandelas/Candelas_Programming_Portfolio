Housekeeping helper (Lab09)
===========================

This repo includes a small helper script to keep the workspace clean during development.

Files
- `scripts/cleanup.sh` — safe housekeeping script. By default it is non-destructive:
  - runs `make clean` if available
  - removes common artifacts: `Lab09_gameFunctions_submission.zip`, `horse`, `test_game`, and `obj/`
  - deletes macOS `.DS_Store` files
  - shows `ccache` stats if `ccache` is installed and can clear it with `--clear-ccache`
  - shows `git clean -fdn` dry-run for untracked files; to actually delete untracked files run `scripts/cleanup.sh --force-clean`

Usage
-----
Run the script from the repository root:

```bash
./scripts/cleanup.sh          # safe, non-destructive
./scripts/cleanup.sh --clear-ccache   # also clear ccache (if installed)
./scripts/cleanup.sh --clean-untracked  # shows git clean dry-run
./scripts/cleanup.sh --force-clean  # DESTRUCTIVE: removes all untracked files (use with caution)
```

Notes
-----
- The script is intentionally conservative. The destructive `git clean -fdx` step runs only with `--force-clean`.
- If you prefer a local-only helper, copy `scripts/cleanup.sh` to a private location and run it there.
