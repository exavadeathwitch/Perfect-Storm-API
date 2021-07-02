#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "mem.h"
#pragma comment(lib, "XInput.lib")
#include <Xinput.h>
#include "MinHook.h"
#include "ccGeneralGameFunctions.h"
#include "d3dcompiler_47_og.h"
#include "HookFunctions.h"
#include "ccMain.h"
#include "Training.h"
using namespace moddingApi;
using namespace std;

//Online Room Name
typedef void(__fastcall* SetRoomName) (__int64 BaseLobbyAddr);
SetRoomName oSetRoomName = NULL;

void __fastcall mem::nSetRoomName(__int64 BaseLobbyAddr)
{
	oSetRoomName(BaseLobbyAddr);
	*(std::uintptr_t*)(BaseLobbyAddr + 0x64) = 15;
}


std::uintptr_t addrGameBase = (std::uintptr_t)GetModuleHandle(NULL);
signed typedef __int64(__fastcall* DecreaseHealth) (__int64 a1, __int64 a2, float Damage);
DecreaseHealth oDecreaseHealth = NULL;

signed __int64 __fastcall mem::nDecreaseHealth(__int64 a1, __int64 a2, float Damage)
{
	signed __int64 PlayerAddr; // rax@1
	float Health; // xmm0_4@2
	std::uintptr_t addrGameBase = (std::uintptr_t)GetModuleHandle(NULL);
	typedef signed __int64(__fastcall* FindPlayerAddr) (__int64 a1, unsigned int a2);
	FindPlayerAddr oFindPlayerAddr = (FindPlayerAddr)(addrGameBase + 0x746C98);

	PlayerAddr = oFindPlayerAddr(a1, a2);
	if (PlayerAddr)
	{
		Health = *(float*)(PlayerAddr + 0x10);
		if (Health != 0.0)
			switch(selectedLItem)
			{
			case 0:
				* (float*)(PlayerAddr + 0x10) = Health - Damage;
				break;
			case 1:
				*(float*)(PlayerAddr + 0x10) = 100.0f;
				break;
			case 2:
				*(float*)(PlayerAddr + 0x10) = 30.0f;
				break;
			}
	}
	if (Debug)	cout << endl << "PlayerAddr: " << PlayerAddr << endl << "Old Health: " << Health << endl << "Damage Taken: " << Damage << endl << "New Health: " << Health - Damage << endl; //Damage Values
	return PlayerAddr;
}

typedef __int64(__fastcall* DecreaseChakra) (__int64 a1, __int64 a2, float ChakraCost);
DecreaseChakra oDecreaseChakra = NULL;

signed __int64 __fastcall mem::nDecreaseChakra(__int64 a1, __int64 a2, float ChakraCost)
{
	signed __int64 PlayerStateAddr; // rax@1
	float CurrentChakra; // xmm0_4@2
	std::uintptr_t addrGameBase = (std::uintptr_t)GetModuleHandle(NULL);
	typedef signed __int64(__fastcall* FindPlayerAddr) (__int64 a1, unsigned int a2);
	FindPlayerAddr oFindPlayerAddr = (FindPlayerAddr)(addrGameBase + 0x746C98);

	PlayerStateAddr = oFindPlayerAddr(a1, a2);
	if (PlayerStateAddr)
	{
		CurrentChakra = *(float*)(PlayerStateAddr + 0x18);
		if (CurrentChakra != 0.0)
		if (tcheckBox[0] == true)
		{
			*(float*)(PlayerStateAddr + 0x18) = 100.0f;
		}
		else
		{
			*(float*)(PlayerStateAddr + 0x18) = CurrentChakra - ChakraCost;
		}
	}
	if (Debug)	cout << endl << "PlayerAddr: " << PlayerStateAddr << endl << "Current Chakra: " << CurrentChakra << endl << "Chakra Cost: " << ChakraCost << endl << "Net Chakra: " << CurrentChakra - ChakraCost << endl; //Chakra Values
	return PlayerStateAddr;
}

signed typedef __int64(__fastcall* DecreaseSupportGaugeS) (__int64 a1, __int64 a2, float SupportCost);
DecreaseSupportGaugeS oDecreaseSupportGaugeS = NULL;

signed __int64 __fastcall mem::nDecreaseSupportGaugeS(__int64 a1, __int64 a2, float SupportCost)
{
	signed __int64 PlayerStateAddr; // rax@1
	float CurrentSupportGauge; // xmm0_4@2 Decreases support gauge as a result of a support being called for a support jutsu. Not for switching.
	typedef signed __int64(__fastcall* sub_140746CE8) (__int64 a1, int a2);
	sub_140746CE8 osub_140746CE8 = (sub_140746CE8)(addrGameBase + 0x746CE8);
	PlayerStateAddr = osub_140746CE8(a1, a2);
	if (PlayerStateAddr)
	{
		CurrentSupportGauge = *(float*)(PlayerStateAddr + 0x2C);
		if (CurrentSupportGauge != 0.0)
			if (tcheckBox[1] == true)
			{
				*(float*)(PlayerStateAddr + 0x2C) = 100.0f;
			}
			else
			{
				*(float*)(PlayerStateAddr + 0x2C) = CurrentSupportGauge - SupportCost;
			}
	}
	return PlayerStateAddr;
}

signed typedef __int64(__fastcall* DecreaseSupportGaugeLS) (__int64 a1, int a2, int Uselessvar, int NewSupportGaugeLevel);
DecreaseSupportGaugeLS oDecreaseSupportGaugeLS = NULL;

signed __int64 __fastcall mem::nDecreaseSupportGaugeLS(__int64 a1, int a2, int Uselessvar, int NewSupportGaugeLevel)
{
	if (tcheckBox[1] == true)
	{
		signed __int64 PlayerStateAddr; // rax@1 Decreases support gauge as a result of switching. Not for support jutsu.
		typedef signed __int64(__fastcall* sub_140746CE8) (__int64 a1, int a2);
		sub_140746CE8 osub_140746CE8 = (sub_140746CE8)(addrGameBase + 0x746CE8);
		PlayerStateAddr = osub_140746CE8(a1, a2);
		if (PlayerStateAddr)
		{
			*(float*)(PlayerStateAddr + 0x2C) = 100.0f;
		}
		return PlayerStateAddr;
	}
	oDecreaseSupportGaugeLS(a1, a2, Uselessvar, NewSupportGaugeLevel);
}

typedef __int64(__fastcall* DecreaseGuardHealth) (__int64 a1, float GuardHealthSubtracted, int a3, int a4, int a5);
DecreaseGuardHealth oDecreaseGuardHealth = NULL;

__int64 __fastcall mem::nDecreaseGuardHealth(__int64 a1, float GuardHealthSubtracted, int a3, int a4, int a5)
{
	float CurrentGuardHealth; // xmm3_4@1
	float NewGuardHealth; // xmm0_4@1

	CurrentGuardHealth = *(float*)(a1 + 8);
	if (tcheckBox[2] == true)
	{
		NewGuardHealth = 25.0f;
	}
	else
	{
		NewGuardHealth = *(float*)(a1 + 8) - GuardHealthSubtracted;
	}
	if (NewGuardHealth == 0.0)
		NewGuardHealth = 0.0;
	if (!a3)
		*(float*)(a1 + 8) = NewGuardHealth;
	if (Debug)	cout << endl << "PlayerAddr: " << a1 + 0x8 << endl << "Current Guard Health: " << CurrentGuardHealth << endl << "Guard Damage: " << CurrentGuardHealth - NewGuardHealth << endl << "New Guard Health: " << NewGuardHealth << endl; //Guard Health Values
	return NewGuardHealth <= 0.0 && CurrentGuardHealth <= 0.0 || a4 && NewGuardHealth <= 0.0 || a5;
}

typedef __int64(__fastcall* DecreaseSubs) (__int64 a1, unsigned int a2, int Uselessvar, int NewSub);
DecreaseSubs oDecreaseSubs = NULL;

signed __int64 __fastcall mem::nDecreaseSubs(__int64 a1, unsigned int a2, int Uselessvar, int NewSub)
{
	if (tcheckBox[3] == true)
	{
		signed __int64 PlayerStateAddr; // rax@1
		typedef signed __int64(__fastcall* FindPlayerAddr) (__int64 a1, unsigned int a2);
		FindPlayerAddr oFindPlayerAddr = (FindPlayerAddr)(addrGameBase + 0x746C98);
		PlayerStateAddr = oFindPlayerAddr(a1, a2);
		if (PlayerStateAddr)
			*(float*)(PlayerStateAddr + 0x20) = 100.0f;
		return PlayerStateAddr;
	}
	oDecreaseSubs(a1, a2, Uselessvar, NewSub);
}

typedef __int64(__fastcall* DecreaseTools) (__int64 a1, unsigned int a2, int MaxTool, int NewTool);
DecreaseTools oDecreaseTools = NULL;

signed __int64 __fastcall mem::nDecreaseTools(__int64 a1, unsigned int a2, int MaxTool, int NewTool)
{
	if (tcheckBox[4] == true)
	{
		int NewToolCount; // ebx@1
		__int64 MaxToolCount; // rdi@1
		signed __int64 PlayerStateAddr; // rax@1

		NewToolCount = NewTool;                       // New number of each tool in each category
		MaxToolCount = MaxTool;                       // Original number of each tool in each category as loaded from duelplayerparam
		typedef signed __int64(__fastcall* FindPlayerAddr) (__int64 a1, unsigned int a2);
		FindPlayerAddr oFindPlayerAddr = (FindPlayerAddr)(addrGameBase + 0x746C98);
		PlayerStateAddr = oFindPlayerAddr(a1, a2);
		if (PlayerStateAddr)
			*(int*)(PlayerStateAddr + 4 * MaxToolCount + 0x48) = 2;
		return PlayerStateAddr;
	}
	oDecreaseTools(a1, a2, MaxTool, NewTool);
}

typedef __int64(__fastcall* IncreaseStormGauge) (__int64 BaseAddr, float Increment);
IncreaseStormGauge oIncreaseStormGauge = NULL;

void __fastcall mem::nIncreaseStormGauge(__int64 BaseAddr, float Increment)
{
	float CurrentStormGauge; // xmm0_4@1
	float NewStormGauge; // xmm0_4@2

	CurrentStormGauge = *(float*)(BaseAddr + 0x34);

	if (selectedSGItem == 1 || selectedSGItem == 2)
	{
		if (CurrentStormGauge < 100.0)
		{
			NewStormGauge = CurrentStormGauge + Increment;
			if (selectedSGItem == 1)
			{
				*(float*)(BaseAddr + 0x34) = 0.0f;
			}
			if (selectedSGItem == 2)
			{
				*(float*)(BaseAddr + 0x34) = 100.0f;
			}
			if (NewStormGauge > 100.0)
				*(int*)(BaseAddr + 0x34) = 1120403456;
		}
	}
	if (Debug)	cout << endl << "PlayerAddr: " << BaseAddr + 0x34 << endl << "Current Storm Gauge: " << CurrentStormGauge << endl << "Increment: " << Increment << endl << "New Storm Gauge: " << CurrentStormGauge + Increment << endl; //Storm Gauge Values
	if (selectedSGItem == 0)
	oIncreaseStormGauge(BaseAddr, Increment);
}

void mem::GeneralHook()
{
	std::uintptr_t addrDecreaseHealth = (std::uintptr_t)(addrGameBase + 0x746E50);
	std::uintptr_t addrDecreaseChakra = (std::uintptr_t)(addrGameBase + 0x746DD0);
	std::uintptr_t addrDecreaseSupportGaugeS = (std::uintptr_t)(addrGameBase + 0x746ED0);
	std::uintptr_t addrDecreaseSupportGaugeLS = (std::uintptr_t)(addrGameBase + 0x7473B8);
	std::uintptr_t addrDecreaseGuardHealth = (std::uintptr_t)(addrGameBase + 0x767F24);
	std::uintptr_t addrDecreaseSubs = (std::uintptr_t)(addrGameBase + 0x74718C);
	std::uintptr_t addrDecreaseTools = (std::uintptr_t)(addrGameBase + 0x7472A0);
	std::uintptr_t addrIncreaseStormGauge = (std::uintptr_t)(addrGameBase + 0x747074);
	bool status = MH_CreateHook((LPVOID)addrDecreaseHealth, &mem::nDecreaseHealth, reinterpret_cast<LPVOID*>(&oDecreaseHealth));
	if (status != MH_OK)
	{
		cout << "could not create hook 2" << endl;
	}

	status = MH_EnableHook((LPVOID)addrDecreaseHealth);
	if (status != MH_OK)
	{
		cout << "could not enable hook 2" << endl;
	}

	status = MH_CreateHook((LPVOID)addrDecreaseChakra, &mem::nDecreaseChakra, reinterpret_cast<LPVOID*>(&oDecreaseChakra));
	if (status != MH_OK)
	{
		cout << "could not create hook 2" << endl;
	}

	status = MH_EnableHook((LPVOID)addrDecreaseChakra);
	if (status != MH_OK)
	{
		cout << "could not enable hook 2" << endl;
	}

	status = MH_CreateHook((LPVOID)addrDecreaseSupportGaugeS, &mem::nDecreaseSupportGaugeS, reinterpret_cast<LPVOID*>(&oDecreaseSupportGaugeS));
	if (status != MH_OK)
	{
		cout << "could not create hook 2" << endl;
	}

	status = MH_EnableHook((LPVOID)addrDecreaseSupportGaugeS);
	if (status != MH_OK)
	{
		cout << "could not enable hook 2" << endl;
	}

	status = MH_CreateHook((LPVOID)addrDecreaseSupportGaugeLS, &mem::nDecreaseSupportGaugeLS, reinterpret_cast<LPVOID*>(&oDecreaseSupportGaugeLS));
	if (status != MH_OK)
	{
		cout << "could not create hook 2" << endl;
	}

	status = MH_EnableHook((LPVOID)addrDecreaseSupportGaugeLS);
	if (status != MH_OK)
	{
		cout << "could not enable hook 2" << endl;
	}

	status = MH_CreateHook((LPVOID)addrDecreaseGuardHealth, &mem::nDecreaseGuardHealth, reinterpret_cast<LPVOID*>(&oDecreaseGuardHealth));
	if (status != MH_OK)
	{
		cout << "could not create hook 2" << endl;
	}

	status = MH_EnableHook((LPVOID)addrDecreaseGuardHealth);
	if (status != MH_OK)
	{
		cout << "could not enable hook 2" << endl;
	}

	status = MH_CreateHook((LPVOID)addrDecreaseSubs, &mem::nDecreaseSubs, reinterpret_cast<LPVOID*>(&oDecreaseSubs));
	if (status != MH_OK)
	{
		cout << "could not create hook 2" << endl;
	}

	status = MH_EnableHook((LPVOID)addrDecreaseSubs);
	if (status != MH_OK)
	{
		cout << "could not enable hook 2" << endl;
	}

	status = MH_CreateHook((LPVOID)addrDecreaseTools, &mem::nDecreaseTools, reinterpret_cast<LPVOID*>(&oDecreaseTools));
	if (status != MH_OK)
	{
		cout << "could not create hook 2" << endl;
	}

	status = MH_EnableHook((LPVOID)addrDecreaseTools);
	if (status != MH_OK)
	{
		cout << "could not enable hook 2" << endl;
	}
	status = MH_CreateHook((LPVOID)addrIncreaseStormGauge, &mem::nIncreaseStormGauge, reinterpret_cast<LPVOID*>(&oIncreaseStormGauge));
	if (status != MH_OK)
	{
		cout << "could not create hook 2" << endl;
	}

	status = MH_EnableHook((LPVOID)addrIncreaseStormGauge);
	if (status != MH_OK)
	{
		cout << "could not enable hook 2" << endl;
	}
}
void mem::PerfectStormHook()
{
	std::uintptr_t addrGameBase = (std::uintptr_t)GetModuleHandle(NULL);
	std::uintptr_t addrSetRoomName = (std::uintptr_t)(addrGameBase + 0x678918);
	MH_STATUS status = MH_CreateHook((LPVOID)addrSetRoomName, &mem::nSetRoomName, reinterpret_cast<LPVOID*>(&oSetRoomName));
	if (status != MH_OK)
	{
		cout << "could not create hook" << endl;
	}

	status = MH_EnableHook((LPVOID)addrSetRoomName);
	if (status != MH_OK)
	{
		cout << "could not enable hook" << endl;
	}
	
}

BYTE ccGeneralGameFunctions::MAX_GAME_VERSION = 9;

// GAME INFO HOOK
void * ccGeneralGameFunctions::PTR_GAMEINFO_00 = 0;
typedef uintptr_t (__fastcall * gameinfohook)(uintptr_t);
gameinfohook g_GameInfoHook;
BYTE originalGameInfoFunction[15];
void UndoGameInfoHook();
uintptr_t __fastcall ccGeneralGameFunctions::SetGameInfoPointer(uintptr_t a1)
{
	UndoGameInfoHook();

	g_GameInfoHook = (gameinfohook)(d3dcompiler_47_og::moduleBase + 0xA03E90);
	uintptr_t result = g_GameInfoHook(a1);
	ccGeneralGameFunctions::PTR_GAMEINFO_00 = (void*)result;
	cout << "Game Info: " << std::hex << ccGeneralGameFunctions::PTR_GAMEINFO_00 << endl;

	ccGeneralGameFunctions::DoGameInfoHook();
	
	return result;
}
uintptr_t GameInfoHookAddress = 0xA03E90;
void ccGeneralGameFunctions::DoGameInfoHook()
{
	memcpy(originalGameInfoFunction, (void*)(d3dcompiler_47_og::moduleBase + 0xA03E90), 15);
	HookFunctions::Hook((void*)(d3dcompiler_47_og::moduleBase + 0xA03E90), (void*)(ccGeneralGameFunctions::SetGameInfoPointer), 15);
}
void UndoGameInfoHook()
{
	DWORD dwOld = 0;
	VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + 0xA03E90), 15, PAGE_EXECUTE_READWRITE, &dwOld);
	memcpy((void*)(d3dcompiler_47_og::moduleBase + 0xA03E90), originalGameInfoFunction, 15);
	VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + 0xA03E90), 15, dwOld, &dwOld);
}

// CPK LOADING
void ccGeneralGameFunctions::CpkLoadList()
{
	BYTE function[] = { 0x48, 0x8D, 0x05, 0x2A, 0x7A, 0x88, 0x00,
						0x89, 0x74, 0x24, 0x38, 0x89, 0x74, 0x24, 0x48,
						0xFF, 0x25, 0x00, 0x00, 0x00, 0x00, // jmp qword ptr [$+6]
						0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ptr
	};

	int StringLength = 0x20;
	vector<string> CpkList;

	CpkList.push_back("sim:data/launch/data1.cpk");
	CpkList.push_back("sim:data/launch/stage1.cpk");
	CpkList.push_back("disc:data/launch/dataRegion.cpk");
	CpkList.push_back("sim:data/launch/sound.cpk");
	CpkList.push_back("disc:data/launch/adx2.cpk");
	CpkList.push_back("disc:data/launch/movie1.cpk");
	CpkList.push_back("sim:data/launch/data12.cpk");
	CpkList.push_back("sim:data/launch/data13.cpk");

	// Alloc function
	void * main_malloc = VirtualAlloc(0, sizeof(function) + (CpkList.size() * StringLength), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

	cout << "CPK LOAD: " << std::hex << (uintptr_t)main_malloc << endl;

	//memcpy(main_malloc, (void*)&function, sizeof(function));

	// Set up jump to go back to function
	uintptr_t addressToJump = d3dcompiler_47_og::RecalculateAddress(0x8501B7);
	memcpy((void*)((uintptr_t)&function[0] + 21), (void*)&addressToJump, 8);

	// Write cpk list in memory
	void * cpk_list = (void*)((uintptr_t)&function[0] + sizeof(function));
	int distance1 = (uintptr_t)cpk_list - ((uintptr_t)&function[0] + 7);
	memcpy((void*)((uintptr_t)&function[0] + 3), (void*)&distance1, 4);

	for (int x = 0; x < CpkList.size(); x++)
	{
		cout << "Address: " << std::hex << (uintptr_t)((uintptr_t)main_malloc + (StringLength * x)) << endl;
		memcpy((void*)((uintptr_t)main_malloc + sizeof(function) + (StringLength * x)), (void*)(CpkList[x].c_str()), CpkList[x].length());
	}

	memcpy(main_malloc, (void*)&function[0], sizeof(function));

	DWORD dwOld = 0;
	VirtualProtect(main_malloc, sizeof(function), PAGE_EXECUTE_READWRITE, &dwOld);

	HookFunctions::Hook((void*)(d3dcompiler_47_og::moduleBase + 0x8501A7), main_malloc, 15);
}

// SET MAX VERSION NUMBER
int ccGeneralGameFunctions::SetMaxVersion()
{
	uintptr_t mem_maxVer = d3dcompiler_47_og::moduleBase + 0x85c5b4;

	DWORD dwOld = 0;
	VirtualProtect((void*)mem_maxVer, 1, PAGE_EXECUTE_READWRITE, &dwOld);

	*(BYTE*)((DWORD_PTR)mem_maxVer) = ccGeneralGameFunctions::MAX_GAME_VERSION;

	VirtualProtect((void*)mem_maxVer, 1, dwOld, &dwOld);

	return 0;
}

// GET VERSION NUMBER
typedef DWORD(__stdcall * get_version_number)();
get_version_number g_GetVersionNumber;
int ccGeneralGameFunctions::GetVersionNumber()
{
	g_GetVersionNumber = (get_version_number)(d3dcompiler_47_og::moduleBase + 0x85CC78);
	return g_GetVersionNumber();
}

// GET VERSION STRING
char* ccGeneralGameFunctions::GetVersionString()
{
	int v = GetVersionNumber();

	char* Version[10] = {
		"1.00",
		"1.01",
		"1.02",
		"1.03",
		"1.04",
		"1.05",
		"1.06",
		"1.07",
		"1.08",
		"1.09",
	};

	return Version[v];
}

// GET VERSION STRING API
char* ccGeneralGameFunctions::GetVersionStringAPI()
{
	char* Version = "2.0b (Beta)";
	if (ModOption == 0)
	{
		Version = "1.07 (Enhanced)";
	};

	return Version;
}

// GET RYO POINTER
typedef uintptr_t(__cdecl * get_ryo_pointer)();
get_ryo_pointer g_GetRyoPointer;
uintptr_t ccGeneralGameFunctions::GetRyoPointer()
{
g_GetRyoPointer = (get_ryo_pointer)(d3dcompiler_47_og::moduleBase + 0x51C11C);
return g_GetRyoPointer();
}

// GET GAME MONEY
typedef int(__cdecl * get_game_money)();
get_game_money g_GetGameMoney;
int ccGeneralGameFunctions::GetGameMoney()
{
	g_GetGameMoney = (get_game_money)(d3dcompiler_47_og::moduleBase + 0x4DEAB8);
	return g_GetGameMoney();
}

// GAME MESSAGE TO STRING
typedef char *(__fastcall * message_to_string)(char *);
message_to_string g_MessageToString;
char* ccGeneralGameFunctions::MessageToString(char* msg)
{
	typedef char* (__fastcall* message_to_string)(char*);
	message_to_string g_MessageToString;
	g_MessageToString = (message_to_string)(d3dcompiler_47_og::moduleBase + 0x4E89C4);
	return g_MessageToString(msg);
}

// HOOK OPEN ADV MESSAGE
typedef int *(__fastcall * openmsg)(char *);
openmsg g_OpenMsg;
int ccGeneralGameFunctions::OpenAdvMessageById(char * a)
{
	g_OpenMsg = (openmsg)(d3dcompiler_47_og::moduleBase + 0x4DB9F4);
	g_OpenMsg(a);
	return 0;
}

// START LOAD
typedef int *(__stdcall * startload)();
startload g_StartLoad;
int ccGeneralGameFunctions::StartLoad()
{
	g_StartLoad = (startload)(d3dcompiler_47_og::moduleBase + 0x65A198);
	return (int)g_StartLoad();
}

// END LOAD
typedef int *(__stdcall * endload)();
endload g_EndLoad;
int ccGeneralGameFunctions::EndLoad()
{
	g_EndLoad = (endload)(d3dcompiler_47_og::moduleBase + 0x32CAE8);
	return (int)g_EndLoad();
}

// Load CPK
typedef uintptr_t(__fastcall * readcpk)(char *, void *, uint16_t);
readcpk g_ReadCpk;
int ccGeneralGameFunctions::cpkcount = 0;
uintptr_t ccGeneralGameFunctions::Cpk_LoadXfbin(void * path)
{
	g_ReadCpk = (readcpk)(d3dcompiler_47_og::moduleBase + 0x56AA4C);

	if (true)
	{
		char a[100];
		//cout << "Loading cpk: " << std::hex << path << endl;

		ccGeneralGameFunctions::cpkcount++;
		return g_ReadCpk((char*)path, a, 0);
	}
}

// Get mod list string
std::string GetModMessage()
{
	string st = "<color red>Naruto Storm 4</color> Modding API by Zealot Tormunds\n\n";
	if (ccMain::ModList.size() > 0)
	{
		st = st + "<color yellow>Mod List:</color>\n";
		for (int x = 0; x < ccMain::ModCount; x++)
		{
			st = st + "> " + ccMain::ModList[x];
			if (ccMain::ModAuth[x] != "") st = st + " <color yellow>(" + ccMain::ModAuth[x] + ")</color>\n";
			else st = st + "\n";
		}

		st = st + "\n";
		st = st + "<color yellow>" + to_string(ccMain::ModList.size()) + " mods installed</color>";
	}
	else
	{
		st = st + "<color yellow>No mods installed</color>\n";
	}
	return st;
}

vector<std::string> ccGeneralGameFunctions::MessageID;
vector<std::string> ccGeneralGameFunctions::MessageStr;
char ccGeneralGameFunctions::ViewMessageConversions = 0;

uintptr_t ccGeneralGameFunctions::Hook_MsgToString(uintptr_t MessageToDecode)
{
	if (ccGeneralGameFunctions::ViewMessageConversions == 0 && strlen((char*)MessageToDecode) > 0 && *(char*)MessageToDecode != '+')
	{
		HookFunctions::UndoMessageInfoHook();
		char* result = ccGeneralGameFunctions::MessageToString((char*)MessageToDecode);
		HookFunctions::DoMessageInfoHook();

		if (MessageToDecode != 0)
		{
			bool finished = false;

			string message((char*)MessageToDecode);

			if (message == "network_agreement_EU_s-A" || message == "network_agreement_s-A")
			{
				result = (char*)GetModMessage().c_str();
				finished = true;
			}
			else if (message == "network_agreementp2_EU_s-A" || message == "network_agreementp2_s-A")
			{
				result = "";
				finished = true;
			}

			if (finished == false)
			{
				std::string msg = (std::string)(char*)MessageToDecode;

				if (msg == "network_agreement_select") result = "Press any button to continue";
				else if (msg == "network_agreement_ok") result = "";
				else if (msg == "network_agreement_ng") result = "<icon btn_2 />";
				else
				{
					for (int x = 0; x < MessageID.size(); x++)
					{
						if (msg == MessageID[x])
						{
							result = (char*)MessageStr[x].c_str();
						}
					}
				}
				if (msg != (std::string)(char*)MessageToDecode) result = (char*)msg.c_str();
			}
		}

		return (uintptr_t)result;
	}
	else
	{
		if (*(char*)MessageToDecode == '+')
		{
			return (MessageToDecode + 1);
		}

		return MessageToDecode;
	}
}

typedef char* (__fastcall* message_to_string2)(char*);
message_to_string2 g_MessageToString2;

uintptr_t ccGeneralGameFunctions::Hook_MsgToString_Alt(uintptr_t MessageToDecode)
{
	g_MessageToString2 = (message_to_string2)(d3dcompiler_47_og::moduleBase + 0xAB87D0);

	if (ccGeneralGameFunctions::ViewMessageConversions == 0 && strlen((char*)MessageToDecode) > 0 && *(char*)MessageToDecode != '+')
	{
		HookFunctions::UndoMessageInfoHook2();
		char* result = g_MessageToString2((char*)MessageToDecode);
		HookFunctions::DoMessageInfoHook2();

		if (MessageToDecode != 0)
		{
			bool finished = false;

			string message((char*)MessageToDecode);

			if (message == "network_agreement_EU_s-A" || message == "network_agreement_s-A")
			{
				result = (char*)GetModMessage().c_str();
				finished = true;
			}
			else if (message == "network_agreementp2_EU_s-A" || message == "network_agreementp2_s-A")
			{
				result = "";
				finished = true;
			}

			if (finished == false)
			{
				std::string msg = (std::string)(char*)MessageToDecode;

				if (msg == "network_agreement_select") result = "Press any button to continue";
				else if (msg == "network_agreement_ok") result = "";
				else if (msg == "network_agreement_ng") result = "<icon btn_2 />";
				else
				{
					for (int x = 0; x < MessageID.size(); x++)
					{
						if (msg == MessageID[x])
						{
							result = (char*)MessageStr[x].c_str();
						}
					}
				}
				if (msg != (std::string)(char*)MessageToDecode) result = (char*)msg.c_str();
			}
		}

		return (uintptr_t)result;
	}
	else
	{

		if (*(char*)MessageToDecode == '+')
		{
			return (MessageToDecode + 1);
		}

		return MessageToDecode;
	}
}


// GAMEPAD FUNCTIONS
bool ccGeneralGameFunctions::TestButton(WORD button)
{
	XINPUT_STATE actualState;
	XInputGetState(0, &actualState);

	bool toReturn = false;

	if (button != 0x5000 && button != 0x6000)
	{
		if ((actualState.Gamepad.wButtons & button) != 0) toReturn = true;
	}
	else
	{
		switch (button)
		{
		case 0x5000:
			if (actualState.Gamepad.bLeftTrigger > 20) toReturn = true;
			break;
		case 0x6000:
			if (actualState.Gamepad.bRightTrigger > 20) toReturn = true;
			break;
		}
	}

	return (actualState.Gamepad.wButtons & button) != 0;
}