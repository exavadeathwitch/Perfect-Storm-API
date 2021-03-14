#ifndef AUTOUPDATER_H
#define AUTOUPDATER_H
#pragma once

#include "urlmon.h"
#include "DownloadProgress.h"
#include <vector>
#pragma lib "urlmon.lib"

using namespace std;

namespace moddingApi
{
    class AutoUpdater
    {
    public:
        string GetModPath();
        void dwFile();
        static string foo();
        vector<string> split(string s, string delimiter);
        bool fileExists(string name);
    };
}

#endif