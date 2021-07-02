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

typedef __int64(__fastcall* checkFPSMatchmaking)();
checkFPSMatchmaking ocheckFPSMatchmaking = NULL;

__int64 ncheckFPSMatchmaking() {
	if (matchmakingFPS == 0)
		return 29;
	else
		return ocheckFPSMatchmaking();
}

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

constexpr unsigned int str2int(const char* str, int h = 0)
{
	return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}

typedef __int64(__fastcall* getInfoFromMemoryString1)(__int64 a1, int a2);
getInfoFromMemoryString1 ogetInfoFromMemoryString1 = NULL;

std::string strFromAddrSmall(__int64 a1) {
	const std::size_t size = 6;
	char chars[size] = "";
	memcpy(chars, reinterpret_cast<char*>(a1), size);
	int sizeString = sizeof(chars) / sizeof(char);
	std::string name = "";
	for (std::size_t i = 0; i < sizeString; i++) {
		name = name + chars[i];
	}
	return name;
}
std::string strFromAddrLarge(__int64 a1) {
	const std::size_t size = 11;
	char chars[size] = "";
	memcpy(chars, reinterpret_cast<char*>(a1), size);
	int sizeString = sizeof(chars) / sizeof(char);
	std::string name = "";
	for (std::size_t i = 0; i < sizeString; i++) {
		name = name + chars[i];
	}
	return name;
}
__int64 __fastcall moddingApi::Memory::getInfoFromMemoryString1(__int64 a1, int a2) {
	std::string initialname = strFromAddrSmall(a1);
	if (initialname == "STAGE_") {
		std::string stageName = strFromAddrLarge(a1);
		char* cstr = &stageName[0];
		switch (str2int(cstr)) {
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62A"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD01B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD03B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD17B"):
			std::cout << stageName << std::endl;
			break;
			/*
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
			*/
		default: std::cout << "Other stage name" << std::endl; break;
		}
	}
	return ogetInfoFromMemoryString1(a1, a2);
}
signed typedef __int64(__fastcall* InitializeccSceneFreeBattleBegin)(BYTE *a1);
InitializeccSceneFreeBattleBegin oInitializeccSceneFreeBattleBegin = NULL;

__int64 __fastcall moddingApi::Memory::nInitializeccSceneFreeBattleBegin(BYTE *a1) {
	std::cout << "Entered Free Battle" << std::endl;
	return oInitializeccSceneFreeBattleBegin(a1);
}

signed typedef int(__fastcall* InitializeccSceneBootRoot)(__int64 a1);
InitializeccSceneBootRoot oInitializeccSceneBootRoot = NULL;

typedef __int64(__fastcall* newPlayerState)(__int64 a1, unsigned int a2, int a3, int a4);
newPlayerState onewPlayerState = NULL;

__int64 __fastcall moddingApi::Memory::nnewPlayerState(__int64 a1, unsigned int a2, int a3, int a4)
{

	//return onewPlayerState(a1, a2, a3, a4);
	/*
	if ((a2 == 63) && (*(DWORD*)(a1 + 0xCC0) == 8)) {
		return 0;
	}
	*/
	std::cout << "test: " << a2 << std::endl;
	//Puppet Gkunai
	//If a counter is inputted, and you are currently in a grab state, if the puppet has a shuriken attack ID, do nothing. Make the puppet have a shuriken state. Do nothing.
	if (a2 == 153) {
		if (*(DWORD*)(a1 + 0xCC0) == 73) {
			if (*(DWORD*)(a1 + 0x16CF60) == 151) {
				return 0;
			}
			*(DWORD*)(a1 + 0x16CBA8) = 67;
			*(DWORD*)(a1 + 0x16CBBC) = 1;
			return 1;
		}
		return 0;
	}
	//Chakra Shuriken Cover Fire Ground
	if ((a2 == 67) && (*(DWORD*)(a1 + 0xCC0) == 214)) {
		a2 = 70;
		return onewPlayerState(a1, a2, a3, a4);
	}

	//Chakra Shuriken Cover Fire Air
	if ((a2 == 68) && (*(DWORD*)(a1 + 0xCC0) == 214)) {
		a2 = 71;
		return onewPlayerState(a1, a2, a3, a4);
	}
	//Tilt, Shuriken, Chakra Shuriken, Grab Switch Priority
	if (a2 == 207 && (*(DWORD*)(a1 + 0xCC0) == 66 || *(DWORD*)(a1 + 0xCC0) == 67 || *(DWORD*)(a1 + 0xCC0) == 70|| *(DWORD*)(a1 + 0xCC0) == 72)){
		return 0;
	}
	//Stun Lock Removal
	if ((*(DWORD*)(a1 + 0xCC0) == 1 && (a2 == 112 || a2 == 2 || a2 == 63 || a2 == 132 || a2 == 4 || a2 == 5))) {
		*(DWORD*)(a1 + 0xCC8) = a2;
		*(DWORD*)(a1 + 0xCDC) = 1;
		return 1;
	}
	return onewPlayerState(a1, a2, a3, a4);
	/*
	std::cout << "stuff: " + a2 << std::endl;
	int v4; // esi@1
	unsigned int NewPlayerState; // edi@1
	__int64 PlayerBaseAddr; // rbx@1
	unsigned int v7; // ebp@2
	unsigned int CurrentPlayerState; // er14@2
	signed __int64 result; // rax@8

	typedef DWORD(__fastcall* sub_79B468) (__int64 a1);
	sub_79B468 osub_79B468 = (sub_79B468)(moddingApi::Memory::moduleBase + 0x79A868 + 0xC00);

	typedef DWORD(__fastcall* sub_79B8B8) (__int64 a1);
	sub_79B8B8 osub_79B8B8 = (sub_79B8B8)(moddingApi::Memory::moduleBase + 0x79ACB8 + 0xC00);

	typedef void(__fastcall* sub_79C8FC) (__int64 a1);
	sub_79C8FC osub_79C8FC = (sub_79C8FC)(moddingApi::Memory::moduleBase + 0x79BCFC + 0xC00);

	v4 = a4;
	NewPlayerState = a2;
	PlayerBaseAddr = a1;
	if (a3 || (v7 = *(DWORD*)(a1 + 0xCC0), CurrentPlayerState = *(DWORD*)(a1 + 0xCC8), osub_79B468 <= 0) && (osub_79B8B8(PlayerBaseAddr) <= 0) && !v4 )
	{
		osub_79C8FC(PlayerBaseAddr);
		result = 1i64;
		std::cout << "test: " << NewPlayerState << std::endl;
		*(DWORD*)(PlayerBaseAddr + 0xCC8) = NewPlayerState;
		*(DWORD*)(PlayerBaseAddr + 0xCDC) = 1;
	}
	else
	{
		result = 0i64;
	}
	return result;
		*/
}

//This function initializes the scene that loads
__int64 __fastcall moddingApi::Memory::nInitializeccSceneBootRoot(__int64 a1) {

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

//This function initializes the scene that loads
__int64 __fastcall moddingApi::Memory::nInitializeccSceneBattleModeSelect(__int64 a1) {
	//std::cout << "in battle mode select" << std::endl;
	BYTE* v1; // rdi@1
	__int64 v2; // rax@1
	__int64 v3; // rbx@1
	__int64 v4; // rax@2

	typedef __int64(__fastcall* sub_A017F0) (size_t a1);
	sub_A017F0 osub_A017F0 = (sub_A017F0)(moddingApi::Memory::moduleBase + 0xA00BF0 + 0xC00);

	typedef __int64(__fastcall* sub_6D671C) (__int64 a1);
	sub_6D671C osub_6D671C = (sub_6D671C)(moddingApi::Memory::moduleBase + 0x6D5B1C + 0xC00);

	typedef __int64(__fastcall* sub_AB4550) (__int64 a1, BYTE* a2);
	sub_AB4550 osub_AB4550 = (sub_AB4550)(moddingApi::Memory::moduleBase + 0xAB3950 + 0xC00);

	v1 = (BYTE*)a1;
	v2 = osub_A017F0(0x188ui64);
	v3 = 0i64;
	if (v2) {
		v3 = osub_6D671C(v2);
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

		std::uintptr_t addrDecreaseHealth = (std::uintptr_t)(moddingApi::Memory::moduleBase + 0x6B39CC + 0xC00);
		std::uintptr_t addrLoadCpkInit = (std::uintptr_t)(moddingApi::Memory::moduleBase + 0x854F3C + 0xC00);
		std::uintptr_t addrNewPlayerState = (std::uintptr_t)(moddingApi::Memory::moduleBase + 0x7ADCB4 + 0xC00);
		std::uintptr_t addrMessageInfo = (std::uintptr_t)(moddingApi::Memory::moduleBase + 0xAB8720 + 0xC00);
		std::uintptr_t addrMemString = (std::uintptr_t)(moddingApi::Memory::moduleBase + 0xA01230 + 0xC00);
		std::uintptr_t addrInitializeccSceneFreeBattleBegin = (std::uintptr_t)(moddingApi::Memory::moduleBase + 0x6DCC64 + 0xC00);
		std::cout << "MinHook Initialized" << std::endl;
		
		bool status = MH_CreateHook((LPVOID)addrDecreaseHealth, &ncheckFPSMatchmaking, reinterpret_cast<LPVOID*>(&ocheckFPSMatchmaking));
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
			std::cout << "could not create hook LoadCpkInit" << std::endl;
		}

		status = MH_EnableHook((LPVOID)addrLoadCpkInit);
		if (status != MH_OK)
		{
			std::cout << "could not enable hook LoadCpkInit" << std::endl;
		}

		status = MH_CreateHook((LPVOID)addrNewPlayerState, &moddingApi::Memory::nnewPlayerState, reinterpret_cast<LPVOID*>(&onewPlayerState));
		if (status != MH_OK)
		{
			std::cout << "could not create hook NewPlayerStat" << std::endl;
		}

		status = MH_EnableHook((LPVOID)addrNewPlayerState);
		if (status != MH_OK)
		{
			std::cout << "could not enable hook NewPlayerStat" << std::endl;
		}

		status = MH_CreateHook((LPVOID)addrMemString, &moddingApi::Memory::getInfoFromMemoryString1, reinterpret_cast<LPVOID*>(&ogetInfoFromMemoryString1));
		if (status != MH_OK)
		{
			std::cout << "could not create hook NewPlayerStat" << std::endl;
		}

		status = MH_EnableHook((LPVOID)addrMemString);
		if (status != MH_OK)
		{
			std::cout << "could not enable hook NewPlayerStat" << std::endl;
		}
		status = MH_CreateHook((LPVOID)addrInitializeccSceneFreeBattleBegin, &moddingApi::Memory::nInitializeccSceneFreeBattleBegin, reinterpret_cast<LPVOID*>(&oInitializeccSceneFreeBattleBegin));
		if (status != MH_OK)
		{
			std::cout << "could not create hook NewPlayerStat" << std::endl;
		}

		status = MH_EnableHook((LPVOID)addrInitializeccSceneFreeBattleBegin);
		if (status != MH_OK)
		{
			std::cout << "could not enable hook NewPlayerStat" << std::endl;
		}
		/*
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
		*/
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
	write_bytes<3>(moddingApi::Memory::moduleBase + 0xB25794 + 0xC00, { 0x90, 0x90, 0x90 });
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