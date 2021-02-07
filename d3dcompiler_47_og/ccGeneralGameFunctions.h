#ifndef CCGENERALGAMEFUNCTIONS_H 
#define CCGENERALGAMEFUNCTIONS_H
#pragma once

#include <vector>
#include <string>

namespace moddingApi
{
	class ccGeneralGameFunctions
	{
	public:
		static char MAX_GAME_VERSION;

		static void * PTR_GAMEINFO_00;
		static void DoGameInfoHook();
		static uintptr_t SetGameInfoPointer(uintptr_t a1);

		static void CpkLoadList();

		static int SetMaxVersion();
		static int GetVersionNumber();
		static char* GetVersionString();
		static char* GetVersionStringAPI();
		static uintptr_t GetRyoPointer();
		static int GetGameMoney();
		static char* MessageToString(char *);

		static void HookLoadXfbin();
		static void HookLoadXfbin2();

		static void HookCpkLoad();
		static void HookCpkLoad2();

		// Files
		static int cpkcount;
		static uintptr_t Cpk_LoadXfbin(void *);

		// Adventure
		static int OpenAdvMessageById(char *);

		// Loading
		static int StartLoad();
		static int EndLoad();

		// Dictionary
		static std::vector<std::string> MessageID;
		static std::vector<std::string> MessageStr;
		static char ViewMessageConversions;

		static uintptr_t Hook_MsgToString(uintptr_t);
		static uintptr_t Hook_MsgToString_Alt(uintptr_t);

		// Gamepad
		static bool TestButton(unsigned short);

		static signed __int64 enablePads();
		static void HookLoadXfbin_C();
		static void HookTest();

		static int GetCurrentFrame();
		static int GetFPS();
		static bool IsFocus();
	};
}

#endif