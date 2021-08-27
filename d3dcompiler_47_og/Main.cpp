#include <iostream>
#include <string>
#include <stdio.h>
#include <filesystem>
#include <fstream>
#include "Main.h"
#include "Console.h"
#include "Settings.h"
#include "Memory.h"
#include "Music.h"

//This is the function that runs after the dll is initialized and proxies the original DLL.
//Runtime functions will be initiated such as hooks, setting up the console, and reading the config file.
DWORD WINAPI moddingApi::Main::MainThread() {
	moddingApi::Console::InitConsole();
	moddingApi::Memory::InitHooks();
	moddingApi::Memory::WriteBytes();
	if (!moddingApi::Main::InitConfig()) {
		//moddingApi::Console::InitConsole();
		std::cout << "Config could not be read. Please make sure that your config.ini file is in " << moddingApi::Main::GetStormDirectory() << "\\PSAPI\\" << std::endl;
		}
		

	moddingApi::Console::LoopConsole();
	return 0;
}

//This is the function that initializes the reading of the config file.
bool moddingApi::Main::InitConfig() {
	char* ConfigPath = strcpy(new char[moddingApi::Main::GetStormDirectory().length() + 1], moddingApi::Main::GetStormDirectory().c_str());
	strcat(ConfigPath, "\\PSAPIBeta\\");
	strcat(ConfigPath, "settings.ini");
	std::ifstream ifile;
	ifile.open(ConfigPath);

	if (!ifile)
		return 0;
	moddingApi::Settings::ReadConfig(ConfigPath);
	return 1;
}

//This is the function that gets the directory of Naruto Storm 4.
std::string moddingApi::Main::GetStormDirectory() {
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	return std::string(buffer) .substr(0, std::string(buffer) .find_last_of("\\/"));
}