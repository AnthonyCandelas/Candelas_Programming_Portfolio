Sanitize cloned repos

This small utility helps you safely work with instructor-provided GitHub clones without
accidentally pushing back to the instructor's remote.

Usage

- Remove .git and only detect instructor links (dry):

  ```bash
  ./tools/sanitize_cloned_repo.sh /path/to/cloned/repo
  ```

- Remove .git and replace known instructor links (automatic replace):

  ```bash
  ./tools/sanitize_cloned_repo.sh /path/to/cloned/repo --auto-replace
  ```

- After sanitizing, you can create a new git repo and add your origin (your URL):

  ```bash
  ./tools/sanitize_cloned_repo.sh /path/to/cloned/repo --init-git git@github.com:YourUser/YourRepo.git
  ```

Notes

- The script removes the `.git` folder in the target directory (this is irreversible for that clone). Only run it on local clones you don't need to push back to.
- The `--auto-replace` option replaces a handful of known instructor domain patterns with a placeholder `<INSTRUCTOR_LINK_REMOVED>`.
- You should review changes made by `--auto-replace` before committing them into your own repo.

Safety

- I will not run this script automatically on your system without your explicit request. If you want, I can run it now on selected folders (for example, `C/Labs/Lab13`) and then initialize the folder as a repo under your remote — but I will only push to your remote when you explicitly instruct me to do so.

Alias / wrapper

- There is a convenient wrapper script `tools/clone_and_sanitize.sh` that runs `git clone` then sanitizes the result. Usage:

```bash
./tools/clone_and_sanitize.sh <repo-url> [target-dir] [--auto-replace] [--init-git <git-url>]
```

- To make cloning easier, you can source `tools/sanitize_alias.sh` from your `~/.zshrc` (or simply copy the function) which provides the `clone_sanitize` function. Example lines to add to `~/.zshrc`:

```bash
# source the helper (adjust the path to match your workspace)
source "/Users/anthonycandelas/Desktop/Desktop Folders/College Course Folders/Fall 2025/Computer Science/tools/sanitize_alias.sh"

# then use:
# clone_sanitize https://github.com/instructor/some-repo.git --auto-replace --init-git git@github.com:YourUser/YourRepo.git
```

Use `--auto-replace` to replace known instructor links automatically. If you pass `--init-git <git-url>`, the sanitizer will initialize a new git repo and set `origin` to that URL so you can push safely to your repository.
