#include "AutoUpdater.h"
#include "DownloadProgress.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
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
    DownloadProgress progress;
    LPCSTR url = "http://perfectstormmod.com/version.txt";
    LPCSTR fName = "version_server.txt";
    string version_game = "100";

    vector<string> path = split(GetModPath(), "\\");
    string download_to = "";

    for (int i = 0; i < path.size(); i++) {
        download_to += path[i] + "\\";
    }

    download_to += fName;
    cout << download_to << endl;

    HRESULT res = URLDownloadToFile(NULL, url, download_to.c_str(), 0, static_cast<IBindStatusCallback*>(&progress));

    if (FAILED(res))
    {
        cout << "AutoUpdater - Failed to download server version file." << endl;
        // do something ...
    }
    /*
    string version_server = "";
    ifstream ifs(fName);
    if (!ifs.is_open()) { cout << " Failed to open server version file." << endl; }
    else {
        getline(ifs, version_server);
    }
    cout << "Version server: " << version_server << ", Version game: " << version_game << endl;
    */
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
