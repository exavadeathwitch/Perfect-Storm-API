import sys
import subprocess
import os
import platform

# Get the current directory.
if getattr(sys, 'frozen', False):
    application_path = os.path.dirname(sys.executable)
elif __file__:
    application_path = os.path.dirname(__file__)

# Get the path for 7zip depending on if it's 32 or 64bit.
if platform.architecture()[0] == "32bit":
    zip_path = os.path.join(application_path, '7za.exe')
elif platform.architecture()[0] == "64bit":
    zip_path = os.path.join(application_path, 'x64', '7za.exe')

# Dictionary for raw string function.
_dRawMap = {8: r'\b', 7: r'\a', 12: r'\f', 10: r'\n', 13: r'\r', 9: r'\t', 11: r'\v'}


def get_raw_string(s: str) -> str:
    """Takes a filepath string and turns it into a raw string."""
    return r''.join(_dRawMap.get(ord(c), c) for c in s)


def extract_files(zip_name: str) -> tuple[bytes, bytes]:
    """Extracts the files using the 7zip exe."""

    # Give a variable system the arguments for the 7zip command line.
    system = subprocess.Popen([get_raw_string(zip_path), "x", "-y", zip_name])

    # Give these arguments to the actual 7zip exe
    return system.communicate()


