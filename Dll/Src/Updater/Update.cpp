#include "pch.hpp"

#include "Update.hpp"

#include "Util/Memory/String.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <WinInet.h>
#include <windows.h>
#include <strsafe.h>
#include <ctime>
/*
std::string Update::function::GetModPath() {
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

void Update::function::dwFile()
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

    LPCSTR hourStr = std::to_string(hour).c_str();
    LPCSTR minStr = std::to_string(min).c_str();
    LPCSTR statusURL = "http://perfectstormmod.com/update/status.txt?CacheBuster=";
    LPCSTR fullURL = (std::string(statusURL) + std::string(hourStr) + std::string(minStr) + (pm ? "pm" : "am")).c_str();
    LPCSTR statusName = "status.txt";
    std::vector<std::string> path = split(GetModPath(), "\\");
    std::string fullPath = "";
    std::string download_to = "";

    for (int i = 0; i < path.size(); i++) {
        fullPath += path[i] + "\\";
    }

    download_to = fullPath + statusName;

    HRESULT res = URLDownloadToFile(NULL, fullURL, download_to.c_str(), 0, NULL);

    while (!fileExists(download_to)) {  }

    std::string status = "";
    std::ifstream ifs(statusName);

    if (!ifs.is_open()) { std::cout << " Failed to open status file." << std::endl; canUpdate = false; }
    else {
        getline(ifs, status);
        ifs.close();
    }

    if (remove(download_to.c_str()) != 0) std::cout << "Error removing status.txt file" << std::endl;
    canUpdate = (status == "ready") ? true : false;

    if (canUpdate) {
        LPCSTR url = "http://perfectstormmod.com/update/version.txt";
        LPCSTR fName = "version_server.txt";
        std::string version_game = "001";

        download_to = fullPath + fName;
        std::cout << "Downloading version diff to " << download_to << std::endl;
        DeleteUrlCacheEntry(download_to.c_str());
        HRESULT res = URLDownloadToFile(NULL, url, download_to.c_str(), 0, NULL);

        while (!fileExists(download_to)) {  }

        std::string version_server = "";
        std::ifstream ifs(fName);

        if (!ifs.is_open()) std::cout << " Failed to open server version file." << std::endl;
        else {
            getline(ifs, version_server);
            ifs.close();
        }

        if (remove(download_to.c_str()) != 0) std::cout << "Error removing version_server.txt file" << std::endl;
        else std::cout << "Successfully removed version_server.txt file" << std::endl;

        std::cout << "Version server: " << version_server << ", Version game: " << version_game << std::endl;
        if (std::stoi(version_server) > std::stoi(version_game)) {
            ShellExecute(NULL, "open", (fullPath + "Perfect Storm Updater.exe").c_str(), NULL, NULL, SW_SHOWDEFAULT);

            exit(EXIT_SUCCESS);
        }
        else {
        }
    }
}

bool Update::function::fileExists(std::string name) {
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

std::string Update::function::foo() {
    return "bar";
}

std::vector<std::string> Update::function::split(std::string s, std::string delimiter) {
    size_t pos = 0;
    std::vector<std::string> token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token.push_back(s.substr(0, pos));
        s.erase(0, pos + delimiter.length());
    }

    return token;
}
*/