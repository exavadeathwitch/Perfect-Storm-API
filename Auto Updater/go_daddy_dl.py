import sys
import time
import urllib.request


def download_from_godaddy(url_given: str) -> None:
    """
    Gets a url and then downloads the file from the given url.
    This function can work with urls from other sites, but it is not guaranteed.
    For now, it is optimised to mainly work with godaddy urls.
    """

    # Create the URL and filename.
    url = url_given
    file_name = url.split('/')[-1]

    # Start the download.
    with urllib.request.urlopen(url) as response, open(file_name, 'wb') as out_file:
        print('File is downloading')
        file_size = response.getheader('content-length')
        file_size_dl = 0
        block_sz = 1396

        # For timing the download.
        start_time = time.time()

        # if there is a file.
        if file_size:
            file_size = int(file_size)
            block_sz = max(4096, file_size // 20)

        # Read the chuck size from the server and write to the system. If the server does not give one, break out of
        # the loop since the download has been completed.
        while True:
            buffer = response.read(block_sz)
            if not buffer:
                break

            if file_size:  # Calculate the download percentage left and the speed.
                file_size_dl += len(buffer)
                out_file.write(buffer)
                done = int(30 * file_size_dl / int(file_size))
                sys.stdout.write(
                    "\r[%s%s] Speed is %s Mbps" % (
                        '=' * done, ' ' * (30 - done), file_size_dl // (time.time() - start_time) / 100000))
                percent = int((file_size_dl / file_size) * 100)
                print(f"\nDownload percentage is : {percent}% ")

    # Print to console when the download is done.
    print(f'\nFile has finished downloading in {(time.time() - start_time) / 60} minutes')
