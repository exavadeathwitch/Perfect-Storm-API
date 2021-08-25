import os
import sys
import shutil



def delete_7z_file() -> None:
    """
    Deletes the Perfect Storm file if it exists
    """
    # Get the current directory.
    if getattr(sys, 'frozen', False):
        application_path = os.path.dirname(sys.executable)
    elif __file__:
        application_path = os.path.dirname(__file__)

    delete_path = os.path.join(application_path, 'PerfectStorm.7z')

    try:
        if os.path.isfile(delete_path):  # if file exists
            os.unlink(delete_path)  # deletes the file
    except OSError as e:
        print(f"\nI can't seem to delete the PerfectStorm.7z file. Please try deleting it manually at this location"
              f"{application_path}")
