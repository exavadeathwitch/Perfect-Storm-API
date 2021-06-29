import os
import sys
import shutil


def delete() -> None:
    """
    This function checks if the 7 and 12 folder are in data/patch,
    If they are, it deletes the 7 folder and renames the 12 folder to 7.
    If only the 12 folder is there, nothing is deleted but the folder is renamed
    and if there is only a 7 folder, nothing is also done.
    """

    # Get the current directory.
    if getattr(sys, 'frozen', False):
        application_path = os.path.dirname(sys.executable)
    elif __file__:
        application_path = os.path.dirname(__file__)

    # Create the path for deleting.
    delete_path = os.path.join(application_path, 'data', 'patch', '7')

    # Create the path for renaming.
    rename_path = os.path.join(application_path, 'data', 'patch', '12')

    # Delete the 7 folder and rename the 12 to 7 only if both paths exist.
    if os.path.exists(delete_path) and os.path.exists(rename_path):
        shutil.rmtree(delete_path)
        if os.path.exists(rename_path):
            os.rename(rename_path, delete_path)

    # Rename the 12 folder to 7.
    if os.path.exists(rename_path):
        os.rename(rename_path, delete_path)


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
