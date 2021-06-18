#include <iostream>
#include <cstdint>
#include <windows.h>
#include <array>

#include "Memory.h"
#include "d3dcompiler_47_og.h"
#include "MinHook.h"
#include "Settings.h"
#include "Message.h"



signed typedef int(__fastcall* InitCPKLoad)();
InitCPKLoad oInitCPKLoad = NULL;

signed typedef int(__fastcall* msgtest)();
msgtest omsgtest = NULL;

signed typedef int(__fastcall* msgtest2)();
msgtest2 omsgtest2 = NULL;

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



template <std::size_t size>
auto moddingApi::Memory::write_bytes(const std::uintptr_t start, const std::array<std::uint8_t, size>& bytes) -> bool {
	DWORD old_prot;

	if (!VirtualProtect(reinterpret_cast<void*>(start), bytes.size(), PAGE_EXECUTE_READWRITE, &old_prot))
		return false;

	for (auto i = 0u; i < bytes.size(); ++i)
		*reinterpret_cast<std::uint8_t*>(start + i) = bytes.at(i);

	VirtualProtect(reinterpret_cast<void*>(start), bytes.size(), old_prot, &old_prot);
	return true;
}



//Initializes our memory hooks through usage of the MinHook library. uintptr_t addresses MUST be local variables.
void moddingApi::Memory::InitHooks() {
	if (MH_Initialize() == MH_OK) {

		//std::uintptr_t addrDecreaseHealth = (std::uintptr_t)(moddingApi::Memory::moduleBase + 0x6E01D4 + 0xC00);
		std::uintptr_t addrLoadCpkInit = (std::uintptr_t)(moddingApi::Memory::moduleBase + 0x854F3C + 0xC00);
		std::cout << "MinHook Initialized" << std::endl;
		
		//bool status = MH_CreateHook((LPVOID)addrDecreaseHealth, &nInitializeccSceneBootRoot, reinterpret_cast<LPVOID*>(&oInitializeccSceneBootRoot));
		//if (status != MH_OK)
		//{
		//	std::cout << "could not create hook 2" << std::endl;
		//}
		/*
		status = MH_EnableHook((LPVOID)addrDecreaseHealth);
		if (status != MH_OK)
		{
			std::cout << "could not enable hook 2" << std::endl;
		}
		*/
		bool status = MH_CreateHook((LPVOID)addrLoadCpkInit, &moddingApi::Settings::LoadCpkInitial, reinterpret_cast<LPVOID*>(&oInitCPKLoad));
		if (status != MH_OK)
		{
			std::cout << "could not create hook 23" << std::endl;
		}

		status = MH_EnableHook((LPVOID)addrLoadCpkInit);
		if (status != MH_OK)
		{
			std::cout << "could not enable hook 23" << std::endl;
		}
		std::uintptr_t addrMessageInfo = (std::uintptr_t)(moddingApi::Memory::moduleBase + 0xAB8720 + 0xC00);
		status = MH_CreateHook((LPVOID)addrMessageInfo, &moddingApi::Message::Hook_MsgToString, reinterpret_cast<LPVOID*>(&omsgtest));
		if (status != MH_OK)
		{
			std::cout << "could not create hook Hook_MsgToString" << std::endl;
		}
		status = MH_EnableHook((LPVOID)addrMessageInfo);
		if (status != MH_OK)
		{
			std::cout << "could not enable hook Hook_MsgToString" << std::endl;
		}
		std::uintptr_t addrMessageInfo2 = (std::uintptr_t)(moddingApi::Memory::moduleBase + 0xAB87D0 + 0xC00);

		status = MH_CreateHook((LPVOID)addrMessageInfo2, &moddingApi::Message::Hook_MsgToString_Alt, reinterpret_cast<LPVOID*>(&omsgtest2));
		if (status != MH_OK)
		{
			std::cout << "could not create hook Hook_MsgToString_Alt" << std::endl;
		}
		status = MH_EnableHook((LPVOID)addrMessageInfo2);
		if (status != MH_OK)
		{
			std::cout << "could not enable hook Hook_MsgToString_Alt" << std::endl;
		}
	}
}
std::vector<BYTE> replace;

void test() {
	replace.push_back(0xFF);
	replace.push_back(0xFF);
	int count = 3;
	DWORD dwOld = 0;
	VirtualProtect((void*)(moddingApi::Memory::moduleBase + 0x7F3EB7 + 0xC00), replace.size(), PAGE_EXECUTE_READWRITE, &dwOld);
	BYTE v[0x1000];
	for (int x = 0; x < count; x++)
	{
		v[x] = replace[x];
	}

	//cout << "Patch";
	//cout << std::hex << d3dcompiler_47_og::moduleBase + Address << endl;
	memcpy((void*)(moddingApi::Memory::moduleBase + 0x7F3EB7 + 0xC00), &v, count - 1);
	VirtualProtect((void*)(moddingApi::Memory::moduleBase + 0x7F3EB7 + 0xC00), replace.size(), dwOld, &dwOld);
}

void moddingApi::Memory::WriteBytes() {
	//Set character limit to FFFF
	write_bytes<2>(moddingApi::Memory::moduleBase + 0x7220C2 + 0xC00, { 0xFF, 0xFF });
	write_bytes<2>(moddingApi::Memory::moduleBase + 0x7F3EB7 + 0xC00, { 0xFF, 0xFF });
	write_bytes<2>(moddingApi::Memory::moduleBase + 0x7F4139 + 0xC00, { 0xFF, 0xFF });
	write_bytes<2>(moddingApi::Memory::moduleBase + 0x8553DB + 0xC00, { 0xFF, 0xFF });
	
	//Disable online microphone for yourself and disable hearing your opponent's microphone
	write_bytes<3>(moddingApi::Memory::moduleBase + 0xB25974 + 0xC00, { 0x90, 0x90, 0x90 });
	write_bytes<3>(moddingApi::Memory::moduleBase + 0xB25966 + 0xC00, { 0x90, 0x90, 0x90 });
	write_bytes<5>(moddingApi::Memory::moduleBase + 0xB260B0 + 0xC00, { 0x90, 0x90, 0x90, 0x90, 0x90 });
	write_bytes<5>(moddingApi::Memory::moduleBase + 0xB26863 + 0xC00, { 0x90, 0x90, 0x90, 0x90, 0x90 });
	write_bytes<5>(moddingApi::Memory::moduleBase + 0xB26B45 + 0xC00, { 0x90, 0x90, 0x90, 0x90, 0x90 });
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

void moddingApi::Message::DoMessageInfoHook()
{
	std::uintptr_t addrMessageInfo = (std::uintptr_t)(moddingApi::Memory::moduleBase + 0xAB8720 + 0xC00);

	bool status = MH_EnableHook((LPVOID)addrMessageInfo);
	if (status != MH_OK)
	{
		std::cout << "could not enable hook Hook_MsgToString" << std::endl;
	}
}

// Fixed
void moddingApi::Message::UndoMessageInfoHook()
{
	std::uintptr_t addrMessageInfo = (std::uintptr_t)(moddingApi::Memory::moduleBase + 0xAB8720 + 0xC00);
	bool status = MH_DisableHook((LPVOID)addrMessageInfo);
	if (status != MH_OK)
	{
		std::cout << "could not disable hook Hook_MsgToString" << std::endl;
	}
}

// Fixed
void moddingApi::Message::DoMessageInfoHook2()
{
	std::uintptr_t addrMessageInfo = (std::uintptr_t)(moddingApi::Memory::moduleBase + 0xAB87D0 + 0xC00);

	bool status = MH_EnableHook((LPVOID)addrMessageInfo);
	if (status != MH_OK)
	{
		std::cout << "could not enable hook Hook_MsgToString_Alt" << std::endl;
	}
}

// Fixed
void moddingApi::Message::UndoMessageInfoHook2()
{
	std::uintptr_t addrMessageInfo = (std::uintptr_t)(moddingApi::Memory::moduleBase + 0xAB87D0 + 0xC00);
	bool status = MH_DisableHook((LPVOID)addrMessageInfo);
	if (status != MH_OK)
	{
		std::cout << "could not disable hook Hook_MsgToString_Alt" << std::endl;
	}
}