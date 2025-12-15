# sanitize_alias.sh
# Add the following to your ~/.zshrc to get a convenient function:
#
# source "/path/to/your/workspace/tools/sanitize_alias.sh"
#
# Then use: clone_sanitize <repo-url> [dest] [--auto-replace] [--init-git <git-url>]

function clone_sanitize() {
  if [ "$#" -lt 1 ]; then
    echo "Usage: clone_sanitize <repo-url> [dest] [--auto-replace] [--init-git <git-url>]"
    return 2
  fi
  local script_dir
  script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
  local clone_script="$script_dir/clone_and_sanitize.sh"
  if [ ! -x "$clone_script" ]; then
    echo "Clone+sanitize script not found or not executable: $clone_script"
    return 2
  fi
  "$clone_script" "$@"
}
