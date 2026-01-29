# WSL Setup & VS Code tips

This project includes several helper `*.sh` scripts (`scripts/*.sh`) that are intended to run in a POSIX shell (bash). On Windows the recommended way to run them is via WSL (Windows Subsystem for Linux) which provides a full Linux userspace.

Quick install (Windows 10/11):

1. Open an elevated PowerShell (Run as Administrator) and run:

```powershell
wsl --install
```

2. Restart the machine if prompted. After reboot open `wsl` or your chosen distro (Ubuntu, etc.) to complete distro setup and create a user account.

3. Install common tools inside WSL if needed (example for Ubuntu):

```bash
sudo apt update && sudo apt install -y build-essential git bash coreutils
```

4. In VS Code install the `Remote - WSL` extension (Microsoft) for the best experience. Open the workspace in WSL using the green remote icon in the lower-left corner.

Using the repo scripts from PowerShell (no Git Bash required)

- I added `scripts/run-in-wsl.ps1` which invokes a given `.sh` helper under WSL. Example from PowerShell (run from repo root):

```powershell
# dry-run example
.\scripts\run-in-wsl.ps1 .\scripts\check_style.sh --all

# run cleanup_workspace in apply mode
.\scripts\run-in-wsl.ps1 .\scripts\cleanup_workspace.sh --apply
```

Notes and tips

- After installing WSL you can open a WSL terminal from VS Code (Terminal → New Terminal → choose WSL). In that terminal you can run the `.sh` scripts directly (`./scripts/check_style.sh --all`).
- If you prefer Git Bash instead of WSL, install "Git for Windows" which includes Git Bash and works fine for many scripts, but WSL matches Linux environments more closely and is recommended.
- If you want, I can add PowerShell-native equivalents of `check_style.sh` and other helpers so everything runs natively in PowerShell (no WSL/WSL wrapper needed). Let me know which scripts you want translated.

Troubleshooting

- If `.\scripts\run-in-wsl.ps1` reports "WSL is not installed", run `wsl --install` as Administrator and follow the prompts.
- If a script relies on Linux-only utilities, install them inside WSL using your distro's package manager (e.g., `apt`).

Links

- Official WSL install docs: https://aka.ms/wslinstall
- VS Code Remote - WSL extension: https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-wsl
