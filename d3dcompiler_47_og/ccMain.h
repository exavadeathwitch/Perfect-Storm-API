#pragma once

#include <vector>
using namespace std;
inline bool ModOption = 1;
inline bool Debug = 0;
namespace moddingApi
{
	class ccMain
	{
	public:
		static DWORD WINAPI Main();
		static DWORD WINAPI LoopConsole();
		static DWORD WINAPI LoopGame();
		static void ReadApiFiles();

		// Mod list variables:
		static int ModCount;
		static vector<std::string> ModList;
		static vector<std::string> ModDesc;
		static vector<std::string> ModAuth;
		static vector<BYTE> ModState;

		// Reload API files
		static void ReloadParamFiles();
	};
}