#pragma once

#include "Core/Mod/Mod.hpp"
#include "Util/Util.hpp"
#include "json/single_include/json.hpp"
class ModLoader {
	std::vector<Mod> mods;
	
	public:
		ModLoader() {

		}
		void LoadMods() {
			std::string directory = (util::getModPath() / "mods").generic_string();
			//Load All Mods
			for (const auto& entry : std::filesystem::directory_iterator(directory))
			{
				//Loading new style mod
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
					mods.push_back(Mod(parsedJson["Name"].get<std::string>(), parsedJson["Description"].get<std::string>(), parsedJson["Author"].get<std::string>(), parsedJson["Priority"].get<int>(), 1, entry.path().string()));
				}
				//Loading old style mod
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
					printf_s("closed file\n");
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
					mods.push_back(Mod(modName, modDesc, modAuth, 100, 0, entry.path().string()));
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
			//Hook each mod
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
								
								// Get InitializePlugin
								typedef void(__stdcall* initfunct)(__int64 moduleBase, std::vector<__int64> functs);
								initfunct funct = (initfunct)GetProcAddress(hGetProcIDDLL, "InitializePlugin");
								uintptr_t mb = (uintptr_t)GetModuleHandle(NULL) + 0xC00;
								if (funct)
									funct(mb, functionExport);
								else std::cout << "PluginSystem :: Init not found in plugin" << std::endl;

								// Get InitializeHooks
								typedef void(__stdcall* hookfunct)(__int64 moduleBase, __int64 hookFunction);
								hookfunct hfunct = (hookfunct)GetProcAddress(hGetProcIDDLL, "InitializeHooks");

								if (hfunct) hfunct(mb, NULL);
								else std::cout << "PluginSystem :: Hook not found in plugin" << std::endl;
								
								// Get GameLoop
								typedef void(__stdcall* initfunctloop)(__int64 moduleBase);
								initfunctloop functloop = (initfunctloop)GetProcAddress(hGetProcIDDLL, "GameLoop");
								/*
								if (functloop) PluginLoop.push_back((__int64)functloop);
								else
								{
									std::cout << "PluginSystem :: Loop not found in plugin" << std::endl;
									PluginLoop.push_back(0);
								}*/
							}
							break;
						}
					}
					break;
				default:
					break;
				}
			}
			/*
				std::string s = entry.path().string();

				char ModName[100];
				int StartIndex = strlen(ApiPath);
				int Count = s.length() - StartIndex;

				strncpy(ModName, &s[StartIndex], 100);

				std::string ModPath = (std::string)(ApiPath)+(std::string)(ModName);
				std::string InfoPath = ModPath + "\\info.txt";

				//cout << InfoPath << endl;

				if (filesystem::exists(InfoPath) == true)
				{
					BYTE actual = 0;
					string modName;
					string modDesc;
					string modAuth;

					ifstream file;
					file.open(InfoPath);

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

					if (modName != "")
					{
						// Read plugins first
						for (const auto& f : filesystem::directory_iterator(ModPath))
						{
							string _file = f.path().string();
							string _ext = _file.substr(_file.length() - 4, 4);

							if (_ext == ".dll")
							{
								char* a = new char[_file.length() + 1];
								strcpy(a, _file.c_str());
								HINSTANCE hGetProcIDDLL = LoadLibrary(a);

								if (!hGetProcIDDLL)
								{
									cout << "PluginSystem :: Error loading plugin " << _file.c_str() << ": ERROR CODE " << std::dec << GetLastError() << endl;
								}
								else
								{
									string pluginname = string(ModName) + "/" + filesystem::path(_file).filename().string();
									PluginList.push_back(hGetProcIDDLL);
									cout << "PluginSystem :: Loaded plugin " << pluginname << endl;

									vector<__int64> functionExport;
									functionExport.push_back((__int64)Input::UpdateKeys);
									functionExport.push_back((__int64)Input::GetKey);
									functionExport.push_back((__int64)Input::GetKeyDown);
									functionExport.push_back((__int64)Input::GetKeyUp);

									// Get InitializePlugin
									typedef void(__stdcall* initfunct)(__int64 moduleBase, vector<__int64> functs);
									initfunct funct = (initfunct)GetProcAddress(hGetProcIDDLL, "InitializePlugin");

									if (funct) funct(d3dcompiler_47_og::moduleBase, functionExport);
									else cout << "PluginSystem :: Init not found in plugin" << endl;

									// Get GameLoop
									typedef void(__stdcall* initfunctloop)(__int64 moduleBase);
									initfunctloop functloop = (initfunctloop)GetProcAddress(hGetProcIDDLL, "GameLoop");

									if (functloop) PluginLoop.push_back((__int64)functloop);
									else
									{
										cout << "PluginSystem :: Loop not found in plugin" << endl;
										PluginLoop.push_back(0);
									}
								}
							}
						}

						// Read API files
						for (const auto& f : filesystem::directory_iterator(ModPath))
						{
							string _file = f.path().string();
							string _ext = _file.substr(_file.length() - 4, 4);
							bool fileManagedByPlugin = false;

							// Send file to plugin
							for (int actualPlugin = 0; actualPlugin < ccMain::PluginList.size(); actualPlugin++)
							{
								HINSTANCE hGetProcIDDLL = ccMain::PluginList.at(actualPlugin);

								typedef bool(__stdcall* filefunct)(__int64 moduleBase, std::string path, vector<BYTE> file);
								filefunct funct = (filefunct)GetProcAddress(hGetProcIDDLL, "ParseApiFiles");
								if (funct)
								{
									fileManagedByPlugin = funct(d3dcompiler_47_og::moduleBase, _file, ReadAllBytes(_file));
								}

								if (fileManagedByPlugin) actualPlugin = ccMain::PluginList.size();
							}

							if (fileManagedByPlugin == false)
							{
								if (_ext == "ns4s")
								{
									vector<string> msg = ReadMessageFile(_file);

									for (int x = 0; x + 1 < msg.size(); x = x + 2)
									{
										ccGeneralGameFunctions::MessageID.push_back(msg[x]);
										ccGeneralGameFunctions::MessageStr.push_back(msg[x + 1]);
									}
								}
								else if (_ext == "ns4p")
								{
									ReadPatchFile(_file);
								}
								else if (_ext == "ns4e")
								{
									ReadScriptFile(_file);
								}
								else if (_ext == ".cpk")
								{
									string cpkinfo = filesystem::path(_file).replace_extension("cpk.info").string();
									if (filesystem::exists(cpkinfo))
									{
										vector<BYTE> fileBytes1 = ReadAllBytes(cpkinfo);
										int priority = fileBytes1[0] + (fileBytes1[1] * 0x100) + (fileBytes1[2] * 0x10000) + (fileBytes1[3] * 0x1000000);

										cout << "CpkLoader :: Priority set for cpk " << string(ModName) << "/" << filesystem::path(_file).filename() << " to " << std::dec << priority << "." << endl;
										string cpkpath = "moddingapi/mods/" + string(ModName) + "/" + filesystem::path(_file).filename().string();
										char* a = new char[cpkpath.length() + 1];
										strcpy(a, cpkpath.c_str());
										GameSettings::CpkToLoad.push_back(a);
										GameSettings::CpkPriority.push_back(priority);
									}
									else
									{
										cout << "CpkLoader :: Info file for cpk " << string(ModName) << "/" << filesystem::path(_file).filename() << " was not found. Setting priority to default (13)." << endl;
										string cpkpath = "moddingapi/mods/" + string(ModName) + "/" + filesystem::path(_file).filename().string();
										char* a = new char[cpkpath.length() + 1];
										strcpy(a, cpkpath.c_str());
										GameSettings::CpkToLoad.push_back(a);
										GameSettings::CpkPriority.push_back(13);
									}
								}
								else if (_file.length() > 0x16 && _file.substr(_file.length() - 0x16, 0x16) == "partnerSlotParam.xfbin")
								{
									ReadPartnerSlotParam(_file);
								}
								else if (_file.length() > 0x16 && _file.substr(_file.length() - 0x16, 0x16) == "specialCondParam.xfbin")
								{
									ReadSpecialConditionParam(_file);
								}
							}
						}
						ccMain::ModCount++;
						ccMain::ModList.push_back(modName);
						ccMain::ModDesc.push_back(modDesc);
						ccMain::ModAuth.push_back(modAuth.substr(0, modAuth.length() - 1));
						ccMain::ModState.push_back(1);

						cout << "Enabling mod \"" << ModName << "\"" << endl;
					}
					else
					{
						cout << "Disabling mod \"" << ModName << "\" - Invalid info file." << endl;
					}
				}
				else
				{
					cout << "Disabling mod \"" << ModName << "\" - No info.txt file found." << endl;
				}
			}*/
		}

};
