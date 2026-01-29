Python starter notes

1) Create a virtual environment in each assignment folder (PowerShell):
   python -m venv .venv
   .\.venv\Scripts\Activate.ps1

2) Install dependencies (empty by default):
   pip install -r requirements.txt

3) Run tests from the assignment folder:
   pytest

Keep tests under tests/ for pytest discovery. Adjust requirements.txt per assignment.
