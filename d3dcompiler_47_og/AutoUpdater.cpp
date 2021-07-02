#include "AutoUpdater.h"
#include "DownloadProgress.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <WinInet.h>
#include <windows.h>
#include <strsafe.h>
#include <ctime> 
using namespace moddingApi;

string AutoUpdater::GetModPath() {
    char path[MAX_PATH];
    HMODULE hm = NULL;
    if (GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
        GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
        (LPCSTR)&foo, &hm) == 0)
    {
        int ret = GetLastError();
        fprintf(stderr, "GetModuleHandle failed, error = %d\n", ret);
        return "failed";
    }
    if (GetModuleFileName(hm, path, sizeof(path)) == 0)
    {
        int ret = GetLastError();
        fprintf(stderr, "GetModuleFileName failed, error = %d\n", ret);
        return "failed";
    }

    return path;
}

void AutoUpdater::dwFile()
{
    bool canUpdate = true;

    time_t now = time(0);
    tm* ltm = localtime(&now);
    bool pm = false;
    int hour = ltm->tm_hour;
    if (hour > 12) {
        hour -= 12;
        pm = true;
    }
    int min = ltm->tm_min;

    LPCSTR hourStr = to_string(hour).c_str();
    LPCSTR minStr = to_string(min).c_str();
    LPCSTR statusURL = "https://pastebin.com/raw/FTzdDnbs";
    LPCSTR fullURL = (string(statusURL) + string(hourStr) + string(minStr) + (pm ? "pm" : "am")).c_str();
    LPCSTR statusName = "status.txt";
    vector<string> path = split(GetModPath(), "\\");
    string fullPath = "";
    string download_to = "";

    for (int i = 0; i < path.size(); i++) {
        fullPath += path[i] + "\\";
    }

    download_to = fullPath + statusName;
    cout << "Downloading server status " << download_to << endl;

    HRESULT res = URLDownloadToFile(NULL, statusURL, download_to.c_str(), 0, NULL);
    while (!fileExists(download_to)) { /* Do nothing until the file exists */ }

    string status = "";
    ifstream ifs(statusName);
    /*
    if (!ifs.is_open()) { cout << " Failed to open status file." << endl; canUpdate = false; }
    else {
        getline(ifs, status);
        ifs.close();
    }

    if (remove(download_to.c_str()) != 0) cout << "Error removing status.txt file" << endl;
    else cout << "Successfully removed status.txt file" << endl;
    */
    cout << "Status: " << status << endl;
    canUpdate = (status == "ready") ? true : false;

    if (canUpdate == 1 || canUpdate == 0) {
        LPCSTR url = "https://pastebin.com/raw/TdJz2b89";
        LPCSTR fName = "version_server.txt";
        string version_game = "004";
        download_to = fullPath + fName;
        cout << "Downloading version diff to " << download_to << endl;
        //DeleteUrlCacheEntry(download_to.c_str());
        HRESULT res = URLDownloadToFile(NULL, url, download_to.c_str(), 0, NULL);

        while (!fileExists(download_to)) { /* Do nothing until the file exists */ }

        string version_server = "";
        ifstream ifs(fName);
        if (!ifs.is_open()) cout << " Failed to open server version file." << endl;
        else {
            getline(ifs, version_server);
            ifs.close();
        }

        cout << "Server Version: " << version_server << endl;
        if (remove(download_to.c_str()) != 0) cout << "Error removing version_server.txt file" << endl;
        else cout << "Successfully removed version_server.txt file" << endl;

        cout << "Version server: " << version_server << ", Version game: " << version_game << endl;
        if (stoi(version_server) > stoi(version_game)) {
            cout << "Perfect Storm is outdated!" << endl;
            ShellExecute(NULL, "open", (fullPath + "Perfect Storm Updater.exe").c_str(), NULL, NULL, SW_SHOWDEFAULT);

            exit(EXIT_SUCCESS);
        }
        else {
            cout << "Perfect Storm is up-to-date!" << endl;
        }
    }
}

bool AutoUpdater::fileExists(string name) {
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

string AutoUpdater::foo() {
    return "bar";
}

vector<string> AutoUpdater::split(string s, string delimiter) {
    size_t pos = 0;
    vector<string> token;
    while ((pos = s.find(delimiter)) != string::npos) {
        token.push_back(s.substr(0, pos));
        s.erase(0, pos + delimiter.length());
    }

    return token;
}
