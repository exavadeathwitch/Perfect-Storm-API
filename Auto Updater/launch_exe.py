import os
import sys


def start_storm4_exe() -> None:
    """
    Launches the storm 4 exe.
    """

    # Get the current directory.
    if getattr(sys, 'frozen', False):
        application_path = os.path.dirname(sys.executable)
    elif __file__:
        application_path = os.path.dirname(__file__)

    # Create the path for the storm 4 exe.
    exe_path = os.path.join(application_path, 'NSUNS4.exe')

    # Start the exe.
    os.startfile(exe_path)

