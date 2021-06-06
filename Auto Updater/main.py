import mediafire_dl
from go_daddy_dl import download_from_godaddy
from zip_extraction import extract_files
from launch_exe import start_storm4_exe
import time
from delete_folders_and_files import delete, delete_7z_file
import requests

pastebin_url = 'https://pastebin.com/raw/48DtyP9p'
r = requests.get(pastebin_url)  # Check if the server or webpage exists.
content = r.text  # Get the actual contents in the pastebin.

delete()  # Call the delete function.

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
        print('I could not start your STORM 4 exe. Please try launching it manually')
        time.sleep(10)
except Exception as e:
    time.sleep(3)
    try:
        print('\n The Link included in the program does not work.')
        url = input(' Please enter a media fire link that downloads the mod files \n :')
        output = 'PerfectStorm.7z'
        mediafire_dl.download(url, output, quiet=False)
        print('\nAttempting to extract the files')
        time.sleep(2)
        extract_files(output)
        print('\nFiles have been successfully extracted')
        time.sleep(1)
        print('\nDeleting the PerfectStorm.7z file.')
        delete_7z_file()  # Call the delete function
        input('\nAll operations have been completed. Please press enter to quit')
        try:
            start_storm4_exe()  # Start the storm 4 exe.
        except FileNotFoundError as e:
            print('I could not start your STORM 4 exe. Please try launching it manually')
            time.sleep(10)
    except Exception as e:
        time.sleep(3)
        try:
            print('\n The link given does not work, attempting to download from the slower server. \n')
            url = '  http://perfectstormmod.com/update/PerfectStorm.7z'
            output = 'PerfectStorm.7z'
            download_from_godaddy(url)  # Change this to the go daddy program
            print('\nAttempting to extract the files')
            time.sleep(2)
            extract_files(output)
            print('\nFiles have been successfully extracted')
            time.sleep(1)
            print('\nDeleting the PerfectStorm.7z file.')
            delete_7z_file()  # Call the delete function
            input('\nAll operations have been completed. Please press enter to quit')
            try:
                start_storm4_exe()  # Start the storm 4 exe.
            except FileNotFoundError as e:
                print('I could not start your STORM 4 exe. Please try launching it manually')
                time.sleep(10)
        except Exception as e:
            time.sleep(3)
            print('\nThe program encountered an issue. Please contact the Administrators of the perfect Storm Mod to'
                  ' Resolve this. Thank you.')
