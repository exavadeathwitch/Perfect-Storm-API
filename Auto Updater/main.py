import mediafire_dl
from go_daddy_dl import download_from_godaddy
from zip_extraction import extract_files
from launch_exe import start_storm4_exe
import time
from delete_folders_and_files import delete_7z_file
import requests

pastebin_url = 'https://pastebin.com/raw/zKsf7cVD'
r = requests.get(pastebin_url)  # Check if the server or webpage exists.
content = r.text  # Get the actual contents in the pastebin.

 # Call the delete function.

try:
    url = content
    output = 'PerfectStorm.7z'
    mediafire_dl.download(url, output, quiet=False)  # Call the mediafire_dl function.
    print('Attempting to extract the files')
    time.sleep(2)  # Pause for 2 seconds.
    extract_files(output)  # Call the extract function with the filename.
    print('\nFiles have been successfully extracted')
    time.sleep(1)
    print('\nDeleting the PerfectStorm.7z file.')
    delete_7z_file()  # Call the delete function
    input('\nAll operations have been completed. Please press enter to quit')
    try:
        start_storm4_exe()  # Start the storm 4 exe.
    except FileNotFoundError as e:
        print('The program could not start the game. Please try launching it manually')
        time.sleep(10)
except Exception as e:
            time.sleep(3)
            print('\nThe program could not download the files from the server. Please download them manually at: ')
            print(url)