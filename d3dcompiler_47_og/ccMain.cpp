#include <WinSock2.h>
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include "ccMain.h"
#include "d3dcompiler_47_og.h"
using namespace moddingApi;
using namespace std;
bool EnableAPI = false;


DWORD WINAPI ccMain::Main()
{
	AllocConsole();
	freopen("conin$", "r", stdin);
	freopen("conout$", "w", stdout);
	freopen("conout$", "w", stderr);
	cout << "wow" << endl;
	return 0;
}