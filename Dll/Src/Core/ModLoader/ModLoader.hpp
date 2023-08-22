#pragma once

#include "Core/Globals.hpp"
#include "Core/Mod/Mod.hpp"
#include "Util/Util.hpp"
#include "json/single_include/json.hpp"
#include "Core/Zealot/Zealot.hpp"
#include "Core/Zealot/API_Console.h"
#include <atlstr.h>
class ModLoader {
	
	public:
		std::vector<Mod> mods;
		ModLoader() {

		}
		void LoadMods(bool* enableConsole, bool* convertMessages, std::string* language, int* maxmodspercolumn) {
			std::string directory = (util::getModPath() / "mods").generic_string();
			//Load All Mods
			for (const auto& entry : std::filesystem::directory_iterator(directory))
			{
				//Loading type 1 mod(stormapi mod)
				if (std::filesystem::exists(entry.path().string() + "\\info.json") == true) {
					std::ifstream fileIn(entry.path().string() + "\\info.json");

					const std::string buffer{ std::istreambuf_iterator<char>(fileIn), std::istreambuf_iterator<char>() };

					fileIn.close();
					auto parsedJson = nlohmann::json::parse(buffer);
					std::string errorname = "Name";
					try {
						parsedJson["Name"].get<std::string>();
						errorname = "Description";
						parsedJson["Description"].get<std::string>();
						errorname = "Author";
						parsedJson["Author"].get<std::string>();
						errorname = "Priority";
						parsedJson["Priority"].get<int>();
					}
					catch (const std::exception& ex) {
						std::string message = "info.json at " + entry.path().string() + " causes an error when loading the key " + errorname + ".";
						std::wstring temp = std::wstring(message.begin(), message.end());
						LPCWSTR wideString = temp.c_str();
						MessageBox(0, wideString, L"Storm API", MB_OK);
						continue;
					}
					mods.push_back(Mod(parsedJson["Name"].get<std::string>(), parsedJson["Description"].get<std::string>(), entry.path().string(), parsedJson["Author"].get<std::string>(), parsedJson["Priority"].get<int>(), 1, entry.path().string()));
				}
				//Loading type 0 mod(moddingapi mod)
				else if (std::filesystem::exists(entry.path().string() + "\\info.txt") == true) {
					BYTE actual = 0;
					std::string modName;
					std::string modDesc;
					std::string modAuth;

					std::ifstream file(entry.path().string() + "\\info.txt");
					while (file.eof() == false && actual < 3)
					{
						char a;
						switch (actual)
						{
						case 0:
							a = file.get();
							if (a == '|') actual = 1;
							else modName = modName + a;
							break;
						case 1:
							a = file.get();
							if (a == '|') actual = 2;
							else modDesc = modDesc + a;
							break;
						case 2:
							a = file.get();
							if (a == '|') actual = 3;
							else modAuth = modAuth + a;
							break;
						}
					}
					file.close();
					if (modName == "") {
						std::string message = "info.txt at " + entry.path().string() + " has an empty modName section.";
						std::wstring temp = std::wstring(message.begin(), message.end());
						LPCWSTR wideString = temp.c_str();
						MessageBox(0, wideString, L"Storm API", MB_OK);
						continue;
					}
					if (modDesc == "") {
						std::string message = "info.txt at " + entry.path().string() + " has an empty modDesc section.";
						std::wstring temp = std::wstring(message.begin(), message.end());
						LPCWSTR wideString = temp.c_str();
						MessageBox(0, wideString, L"Storm API", MB_OK);
						continue;
					}
					if (modAuth == "") {
						std::string message = "info.txt at " + entry.path().string() + " has an empty modAuth section.";
						std::wstring temp = std::wstring(message.begin(), message.end());
						LPCWSTR wideString = temp.c_str();
						MessageBox(0, wideString, L"Storm API", MB_OK);
						continue;
					}
					else {
						modAuth = modAuth.substr(0, modAuth.size() - 2);
					}
					std::cout << modName << " has been loaded." << std::endl;
					mods.push_back(Mod(modName, modDesc, entry.path().string(), modAuth, 100, 0, entry.path().string()));
				}
				else {
					std::string message = "Info file at " + entry.path().string() + " not found. The mod has not been loaded.";
					std::wstring temp = std::wstring(message.begin(), message.end());
					LPCWSTR wideString = temp.c_str();
					MessageBox(0, wideString, L"Storm API", MB_OK);
				}
			}
			//Sort them by Priority
			struct less_than_key
			{
				inline bool operator() (const Mod & mod1, const Mod & mod2)
				{
					return (mod1.priority < mod2.priority);
				}
			};
			std::sort(mods.begin(), mods.end(), less_than_key());
			for (int x = 0; x < mods.size(); x++) {
				switch (mods[x].type) {
				case 0:
					for (const auto& f : std::filesystem::directory_iterator(mods[x].path))
					{
						std::string _file = f.path().string();
						std::string _ext = _file.substr(_file.length() - 4, 4);
						if (_ext != ".dll")
							continue;
						if (_ext == ".dll")
						{
							std::string str = _file;
							std::wstring temp = std::wstring(str.begin(), str.end());
							LPCWSTR wideString = temp.c_str();
							HINSTANCE hGetProcIDDLL = LoadLibrary(wideString);

							if (!hGetProcIDDLL)
							{
								std::cout << "PluginSystem :: Error loading plugin " << _file.c_str() << ": ERROR CODE " << std::dec << GetLastError() << std::endl;
							}
							else
							{
								std::string pluginname = std::string(mods[x].name);
								mods[x].dll = hGetProcIDDLL;
								std::cout << "PluginSystem :: Loaded plugin " << pluginname << std::endl;

								std::vector<__int64> functionExport;
								functionExport.push_back((__int64)Zealot::UpdateKeys);
								functionExport.push_back((__int64)Zealot::GetKey);
								functionExport.push_back((__int64)Zealot::GetKeyDown);
								functionExport.push_back((__int64)Zealot::GetKeyUp);
								// Get InitializePlugin
								typedef void(__stdcall* initfunct)(__int64 moduleBase, std::vector<__int64> funct);
								initfunct f = (initfunct)GetProcAddress(hGetProcIDDLL, "InitializePlugin");
								uintptr_t mb = (uintptr_t)GetModuleHandle(NULL) + 0xC00;
								if (f)
									f(mb, functionExport);
								else
									std::cout << "PluginSystem::Init not found in plugin" << std::endl;
								// Get InitializeHooks
								typedef void(__stdcall* hookfunct)(__int64 moduleBase, __int64 hookFunction);
								hookfunct hfunct = (hookfunct)GetProcAddress(hGetProcIDDLL, "InitializeHooks");
								
								if (hfunct)
									hfunct(mb, (__int64)Zealot::Hook);
								else
									std::cout << "PluginSystem :: Hook not found in plugin" << std::endl;

								typedef void(__stdcall* cmdfunct)(__int64 moduleBase, __int64 cmdFunction);
								cmdfunct cfunct = (cmdfunct)GetProcAddress(hGetProcIDDLL, "InitializeCommands");

								if (cfunct)
									cfunct(mb, (__int64)moddingApi::API_Console::AddCommand);
							}
							break;
						}
					}
					break;
					
				case 1:
					for (const auto& f : std::filesystem::directory_iterator(mods[x].path))
					{
						std::string _file = f.path().string();
						if (_file.substr(_file.length() - 4, 4) == ".dll")
						{
							std::string str = _file;
							std::wstring temp = std::wstring(str.begin(), str.end());
							LPCWSTR wideString = temp.c_str();
							HINSTANCE hGetProcIDDLL = LoadLibrary(wideString);

							if (!hGetProcIDDLL)
							{}
							else
							{
								std::string pluginname = std::string(mods[x].name);
								mods[x].dll = hGetProcIDDLL;
								// Get InitializePlugin
								typedef void(__stdcall* initfunct)(uintptr_t moduleBase, bool* enableConsole, bool* convertMessages, std::string* language, int* maxmodspercolumn);
								initfunct f = (initfunct)GetProcAddress(hGetProcIDDLL, "modEntry");
								uintptr_t mb = (uintptr_t)GetModuleHandle(NULL) + 0xC00;
								if (f)
									f(mb, enableConsole, convertMessages, language, maxmodspercolumn);
								else {
									std::string message = "modEntry could not be loaded for the plugin " + pluginname + ".";
									std::wstring temp = std::wstring(message.begin(), message.end());
									LPCWSTR wideString = temp.c_str();
									MessageBox(0, wideString, L"Storm API", MB_OK);
								}
							}
						}
						else
							continue;
					}
					break;
				default:
					break;
				}
			}
			for (int x = 0; x < mods.size(); x++) {
				if (mods[x].type != 0)
					continue;
				else
					for (int y = 0; y < mods.size(); y++) {
						for (const auto& f : std::filesystem::directory_iterator(mods[y].path))
						{
							std::string _file = f.path().string();
							std::string _ext = _file.substr(_file.length() - 4, 4);

							// Send file to plugin
							if (mods[x].type != 0 || mods[x].dll == NULL)
								continue;
							HINSTANCE hGetProcIDDLL = mods[x].dll;

							uintptr_t mb = (uintptr_t)GetModuleHandle(NULL) + 0xC00;
							typedef bool(__stdcall* filefunct)(__int64 moduleBase, std::string path, std::vector<BYTE> file);
							filefunct funct = (filefunct)GetProcAddress(hGetProcIDDLL, "ParseApiFiles");
							if (funct)
								funct(mb, _file, Zealot::ReadAllBytes(_file));

							// Get GameLoop
							/*
							typedef void(__stdcall* initfunctloop)(__int64 moduleBase);
							initfunctloop functloop = (initfunctloop)GetProcAddress(hGetProcIDDLL, "GameLoop");

							if (functloop) PluginLoop.push_back((__int64)functloop);
							else
							{
								std::cout << "PluginSystem :: Loop not found in plugin" << std::endl;
								PluginLoop.push_back(0);
							}*/
						}
					}
			}
		}
};
