#include <iostream>

#include "Memory.h"
#include "CasualLibrary.hpp"
#include "d3dcompiler_47_og.h"
#include "MinHook.h"
#include "Settings.h"

using namespace Memory::Internal;

Address moddingApi::Memory::CGbaseAddr;

signed typedef int(__fastcall* InitCPKLoad)();
InitCPKLoad oInitCPKLoad = NULL;
/*
signed typedef __int64(__fastcall* DecreaseHealth) (__int64 a1, __int64 a2, float Damage);
DecreaseHealth oDecreaseHealth = NULL;

signed __int64 __fastcall nDecreaseHealth(__int64 a1, __int64 a2, float Damage) {
	signed __int64 PlayerAddr; // rax@1
	float Health; // xmm0_4@2
	std::uintptr_t addrGameBase = (std::uintptr_t)GetModuleHandle(NULL);
	typedef signed __int64(__fastcall* FindPlayerAddr) (__int64 a1, unsigned int a2);
	FindPlayerAddr oFindPlayerAddr = (FindPlayerAddr)(addrGameBase + 0x74A71C + 0xC00);

	PlayerAddr = oFindPlayerAddr(a1, a2);
	if (PlayerAddr) {
		Health = *(float*)(PlayerAddr + 0x10);
		if (Health != 0.0)
			*(float*)(PlayerAddr + 0x10) = 100.0f;// Health - Damage;
		return PlayerAddr;
	}
}
*/

signed typedef int(__fastcall* InitializeccSceneBootRoot)(__int64 a1);
InitializeccSceneBootRoot oInitializeccSceneBootRoot = NULL;

//This function initializes the scene that loads
__int64 __fastcall nInitializeccSceneBootRoot(__int64 a1) {

	BYTE* v1; // rdi@1
	__int64 v2; // rax@1
	__int64 v3; // rbx@1

	typedef __int64(__fastcall* sub_A017F0) (size_t a1);
	sub_A017F0 osub_A017F0 = (sub_A017F0)(moddingApi::Memory::moduleBase + 0xA00BF0 + 0xC00);

	typedef __int64(__fastcall* sub_8638B8) (__int64 a1);
	sub_8638B8 osub_8638B8 = (sub_8638B8)(moddingApi::Memory::moduleBase + 0x862CB8 + 0xC00);

	typedef __int64(__fastcall* sub_AB4550) (__int64 a1, BYTE* a2);
	sub_AB4550 osub_AB4550 = (sub_AB4550)(moddingApi::Memory::moduleBase + 0xAB3950 + 0xC00);

	v1 = (BYTE*)a1;
	v2 = osub_A017F0(0x128ui64);
	v3 = 0i64;
	if (v2) {
		v3 = osub_8638B8(v2);
	}
	osub_AB4550(v3, v1);
	return v3;
}

//Initializes our memory hooks through usage of the MinHook library. uintptr_t addresses MUST be local variables.
void moddingApi::Memory::InitHooks() {
	if (MH_Initialize() == MH_OK) {
		std::uintptr_t addrDecreaseHealth = (std::uintptr_t)(moddingApi::Memory::moduleBase + 0x6E01D4 + 0xC00);
		std::uintptr_t addrLoadCpkInit = (std::uintptr_t)(moddingApi::Memory::moduleBase + 0x854F3C + 0xC00);
		std::cout << "MinHook Initialized" << std::endl;
		
		bool status = MH_CreateHook((LPVOID)addrDecreaseHealth, &nInitializeccSceneBootRoot, reinterpret_cast<LPVOID*>(&oInitializeccSceneBootRoot));
		if (status != MH_OK)
		{
			std::cout << "could not create hook 2" << std::endl;
		}

		status = MH_EnableHook((LPVOID)addrDecreaseHealth);
		if (status != MH_OK)
		{
			std::cout << "could not enable hook 2" << std::endl;
		}
		
		status = MH_CreateHook((LPVOID)addrLoadCpkInit, &moddingApi::Settings::LoadCpkInitial, reinterpret_cast<LPVOID*>(&oInitCPKLoad));
		if (status != MH_OK)
		{
			std::cout << "could not create hook 23" << std::endl;
		}

		status = MH_EnableHook((LPVOID)addrLoadCpkInit);
		if (status != MH_OK)
		{
			std::cout << "could not enable hook 23" << std::endl;
		}
	}
	else
	{
		std::cout << "MinHook not Initialized" << std::endl;
		return;
	}
}

//Initialize Base Address for the CasualGamer Memory Library
void moddingApi::Memory::InitializeCasualLibrary() {

	moddingApi::Memory::CGbaseAddr = getModule("NSUNS4.exe");
}

// Get a QWORD pointer from the game
__int64 moddingApi::Memory::GetQword(__int64 qw) {
	__int64 qwr = qw - 0x140000000;
	return *(__int64*)(moddingApi::Memory::moduleBase + qwr);
}

// Get a DWORD pointer from the game
int moddingApi::Memory::GetDword(__int64 dw) {
	__int64 dwr = dw - 0x140000000;
	return *(int*)(moddingApi::Memory::moduleBase + dwr);
}

// Get a OFFSET pointer from the game
__int64 moddingApi::Memory::GetOffset(__int64 of) {
	return (moddingApi::Memory::moduleBase + of);
}