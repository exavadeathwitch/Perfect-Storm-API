import os
import webbrowser
import ctypes
import time


def find_storm_drive():
    print("Trying to find your directory. Please don't close this window.\n")
    buff_size = ctypes.windll.kernel32.GetLogicalDriveStringsW(0, None)
    buff = ctypes.create_string_buffer(buff_size * 2)
    ctypes.windll.kernel32.GetLogicalDriveStringsW(buff_size, buff)
    letters = list(filter(None, buff.raw.decode('utf-16-le').split(u'\0')))

    path_found = False

    for letter in letters:
        for dirpath, dirnames, filenames in os.walk(letter):
            if r'steamapps\common\NARUTO SHIPPUDEN Ultimate Ninja STORM 4' in dirpath:
                print(f'Your storm directory is located at: \n\n{dirpath}')
                path_found = True
                break
    if not path_found:
        my_link_var = "http://perfectstormmod.com/"
        print(
            f"\nI can't seem to find your STORM 4 Directory. \n\n"
            f"Please go to this link to find out what to do {my_link_var}")

        if input("\nIf you'd like to open the link in your browser, please type yes:\n").lower() == 'yes':
            webbrowser.open(my_link_var)


find_storm_drive()

input('\nPlease press enter to quit')





