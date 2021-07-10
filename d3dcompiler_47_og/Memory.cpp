#include <iostream>
#include <cstdint>
#include <windows.h>
#include <array>
#include <string>

#include "Memory.h"
#include "d3dcompiler_47_og.h"
#include "MinHook.h"
#include "Settings.h"
#include "Message.h"
#include "Scene.h"
#include "Stage.h"

signed typedef int(__fastcall* InitCPKLoad)();
InitCPKLoad oInitCPKLoad = NULL;

signed typedef int(__fastcall* msgtest)();
msgtest omsgtest = NULL;

signed typedef int(__fastcall* msgtest2)();
msgtest2 omsgtest2 = NULL;

typedef __int64(__fastcall* checkFPSMatchmaking)();
checkFPSMatchmaking ocheckFPSMatchmaking = NULL;

__int64 ncheckFPSMatchmaking() {
	return matchmakingFPS;
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



typedef __int64(__fastcall* getInfoFromMemoryString1)(__int64 a1, int a2);
getInfoFromMemoryString1 ogetInfoFromMemoryString1 = NULL;

std::string_view moddingApi::Memory::strFromAddrSmall(__int64 a1) {
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

std::string_view moddingApi::Memory::strFromAddrMax(__int64 a1) {
	const std::size_t size = 30;
	char chars[size] = "";
	memcpy(chars, reinterpret_cast<char*>(a1), size);
	int sizeString = sizeof(chars) / sizeof(char);
	std::string name = "";
	const std::string_view state = reinterpret_cast<const char*>(a1);
	/*
	for (std::size_t i = 0; i < sizeString; i++) {
		if ((moddingApi::Memory::read_bytes<1>(a1) == some_bytes) && (moddingApi::Memory::read_bytes<1>(a1-1) == some_bytes) {
			std::cout << "stuff." << std::endl;
		}
		name = name + chars[i];
	}*/
	return state;
}
__int64 __fastcall moddingApi::Memory::getInfoFromMemoryString1(__int64 a1, int a2) {
	moddingApi::Stage::getStageName(a1);
	return ogetInfoFromMemoryString1(a1, a2);
}
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
	std::cout << "State: " << a2 << std::endl;
	//Puppet Gkunai
	//If a counter is inputted, and you are currently in a grab state, if the puppet has a shuriken attack ID, do nothing. Make the puppet have a shuriken state. Do nothing.
	/*
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
	*/
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
	/*
	//Stun Lock Removal
	if ((*(DWORD*)(a1 + 0xCC0) == 1 && (a2 == 112 || a2 == 2 || a2 == 63 || a2 == 132 || a2 == 4 || a2 == 5))) {
		*(DWORD*)(a1 + 0xCC8) = a2;
		*(DWORD*)(a1 + 0xCDC) = 1;
		return 1;
	}
	*/
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


template<std::size_t size>
auto moddingApi::Memory::read_bytes(const std::uintptr_t address)->std::array<std::uint8_t, size> {
	std::array<std::uint8_t, size> read_bytes{};

	for (auto i = 0u; i < size; ++i)
		read_bytes[i] = *std::bit_cast<std::uint8_t*>(address + i);

	return read_bytes;
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

typedef void(__fastcall* setNoChakraCirclePlayerState)(__int64 a1);
setNoChakraCirclePlayerState oSetNoChakraCirclePlayerState = NULL;

void nSetNoChakraCirclePlayerState(__int64 a1) {
	__int64 playerAddr; // rbx@1
	__int64 v2; // rbp@2
	signed int v3; // er14@2
	signed int v4; // edi@4
	signed int v5; // esi@4
	__int64 v6; // rax@11
	__int64 v7; // rax@23

	playerAddr = a1;
	if (*(DWORD*)(a1 + 0xCC0) != 94)          // If the current state isn't 94
	{
		typedef __int64(__fastcall* sub_1407C0DD8) (__int64 a1, int a2);
		sub_1407C0DD8 osub_1407C0DD8 = (sub_1407C0DD8)(moddingApi::Memory::moduleBase + 0x7C01D8 + 0xC00);

		typedef __int64(__fastcall* sub_1407C0A08) (__int64 a1);
		sub_1407C0A08 osub_1407C0A08 = (sub_1407C0A08)(moddingApi::Memory::moduleBase + 0x7BFE08 + 0xC00);

		typedef __int64(__fastcall* sub_1407C09D8) (__int64 a1);
		sub_1407C09D8 osub_1407C09D8 = (sub_1407C09D8)(moddingApi::Memory::moduleBase + 0x7BFDD8 + 0xC00);

		signed typedef __int64(__fastcall* sub_1407C0CE8) (__int64 a1, int a2);
		sub_1407C0CE8 osub_1407C0CE8 = (sub_1407C0CE8)(moddingApi::Memory::moduleBase + 0x7C00E8 + 0xC00);
		v2 = a1 + 0x218;
		v3 = 0;
		if ((unsigned int)osub_1407C0DD8(a1 + 0x218, 8))
			v3 = 1;
		osub_1407C0A08(v2);
		v4 = 0;
		v5 = 0;
		if ((unsigned int)osub_1407C09D8(v2))
			v4 = 1;
		if (*(BYTE*)(playerAddr + 0x14DD8) & 0x10)
			v5 = 1;
		if ((v3 || v4) && ((*(int(__fastcall**)(__int64))(*(__int64*)playerAddr + 0xEA8i64))(playerAddr) || (*(DWORD*)(playerAddr + 0xCC0) == 4 || *(DWORD*)(playerAddr + 0xCC0) == 5 || *(DWORD*)(playerAddr + 0xCC0) == 6)))
		{
			v6 = *(__int64*)playerAddr;
			if (v5)
			{
				onewPlayerState(playerAddr, 64, 0, 0);
				*(DWORD*)(playerAddr + 0x14DD8) = 0;
			}
			else
			{
				onewPlayerState(playerAddr, 64, 0, 1);
			}
		}
		if ((((*(int(__fastcall**)(__int64, signed __int64))(*(__int64*)playerAddr + 0x1398i64))(playerAddr, 1i64)
			&& (osub_1407C0CE8(v2, 0i64) && v4 || (unsigned int)osub_1407C0DD8(v2, 9)))
			&& (((*(int(__fastcall**)(__int64))(*(__int64*)playerAddr + 0xEC8i64))(playerAddr)) || ((*(DWORD*)(playerAddr + 0xCC0) == 10) || (*(DWORD*)(playerAddr + 0xCC0) == 11) || (*(DWORD*)(playerAddr + 0xCC0) == 12)))))
		{ 
			onewPlayerState(playerAddr, 66, 0, 1);
		}
		if (v3 || v4)
		{
			if ((*(int(__fastcall**)(__int64, __int64))(*(__int64*)playerAddr + 0xEA0i64))(playerAddr, v5 == 0))
			{
				v7 = *(__int64*)playerAddr;
				if (v5)
				{
					onewPlayerState(playerAddr, 63, 0, 0);
					*(DWORD*)(playerAddr + 0x14DD8) = 0;
				}
				else
				{
					onewPlayerState(playerAddr, 63, 0, 1);
				}
			}
		}
	}

	oSetNoChakraCirclePlayerState(a1);
}

typedef __int64(__fastcall playerAnim) (__int64 rcx, int a1, __int64 a2, unsigned int a3, float a4, int a5, int a6);
playerAnim* oPlayerAnim = NULL;

__int64 __fastcall nPlayerAnim(__int64 rcx, int a1, __int64 a2, unsigned int a3, float a4, int a5, int a6) {
	
	oPlayerAnim(rcx, a1, a2, a3, a4, a5, a6);
	return *(__int64*)(rcx + 0x208);
}

typedef __int64(__fastcall setGrabPlayerState) (__int64 a1, float a2);
setGrabPlayerState* oSetGrabPlayerState = NULL;

__int64 __fastcall nSetGrabPlayerState(__int64 a1, float a2) {

	//return oSetGrabPlayerState(a1, a2);
	__int64 v2; // rbp@1
	__int64 v3; // rsi@1
	signed int v4; // ebx@27
	signed int v5; // ebx@36
	signed __int64 v6; // rdx@43
	signed int v7; // ebx@52
	int v8; // eax@52
	int v9; // eax@53
	int v10; // eax@54
	int v11; // eax@55
	int v12; // eax@56
	__int64 v13; // rax@63
	signed int v14; // er14@63
	signed int v15; // edi@63
	signed int v16; // ebx@69
	__int64 v17; // rax@72
	signed __int64 v18; // rdx@88
	signed int v19; // ebx@94
	__int64 v20; // rax@96
	__int64 v21; // zf@96
	__int64 v22; // rax@96
	signed __int64 v23; // rdx@96
	signed int v24; // eax@102
	int v25; // eax@104
	signed __int64 v26; // rdx@104
	signed int v27; // ebx@107
	__int64 v28; // rax@129
	__int64 v29; // rcx@129
	signed __int64 v30; // rdx@130
	int v31; // eax@145
	__int64 v32; // rcx@145
	signed __int64 v33; // r9@147
	signed __int64 v34; // r9@158
	signed int v35; // ebx@162
	int result; // eax@175
	char v37; // [sp+20h] [bp-38h]@65
	float v38; // [sp+28h] [bp-30h]@67


	typedef __int64(__fastcall* sub_1407C0DD8) (__int64 a1, int a2);
	sub_1407C0DD8 osub_1407C0DD8 = (sub_1407C0DD8)(moddingApi::Memory::moduleBase + 0x7C01D8 + 0xC00);

	typedef __int64(__fastcall* sub_1407C09D8) (__int64 a1);
	sub_1407C09D8 osub_1407C09D8 = (sub_1407C09D8)(moddingApi::Memory::moduleBase + 0x7BFDD8 + 0xC00);

	typedef signed __int64(__fastcall* sub_140792ECC) (__int64 a1);
	sub_140792ECC osub_140792ECC = (sub_140792ECC)(moddingApi::Memory::moduleBase + 0x7922CC + 0xC00);

	typedef __int64(__fastcall* sub_1407C0C8C) (__int64 a1);
	sub_1407C0C8C osub_1407C0C8C = (sub_1407C0C8C)(moddingApi::Memory::moduleBase + 0x7C008C + 0xC00);

	typedef __int64(__fastcall* sub_1407A3E24) (__int64 a1, int a2);
	sub_1407A3E24 osub_1407A3E24 = (sub_1407A3E24)(moddingApi::Memory::moduleBase + 0x7A3224 + 0xC00);

	typedef int(__fastcall* sub_1407E0EC0) (int a1, __int64 a2, float a3);
	sub_1407E0EC0 osub_1407E0EC0 = (sub_1407E0EC0)(moddingApi::Memory::moduleBase + 0x7E02C0 + 0xC00);

	typedef __int64(__fastcall* sub_1407DF5AC) (__int64 a1, int a2);
	sub_1407DF5AC osub_1407DF5AC = (sub_1407DF5AC)(moddingApi::Memory::moduleBase + 0x7A3224 + 0xC00);

	typedef int(__fastcall* sub_1407E10A0) (__int64 a1, unsigned int a2);
	sub_1407E10A0 osub_1407E10A0 = (sub_1407E10A0)(moddingApi::Memory::moduleBase + 0x7E04A0 + 0xC00);

	typedef int(__fastcall* sub_140784628) (__int64 a1, int a2);
	sub_140784628 osub_140784628 = (sub_140784628)(moddingApi::Memory::moduleBase + 0x783A28 + 0xC00);

	typedef __int64(__fastcall* sub_1407AC910) (__int64 a1, float a2);
	sub_1407AC910 osub_1407AC910 = (sub_1407AC910)(moddingApi::Memory::moduleBase + 0x7ABD10 + 0xC00);

	typedef __int64(__fastcall* sub_1407C0748) (__int64 a1, int a2);
	sub_1407C0748 osub_1407C0748 = (sub_1407C0748)(moddingApi::Memory::moduleBase + 0x7BFB48 + 0xC00);

	typedef int(__fastcall* sub_14079C5C0) (__int64 a1);
	sub_14079C5C0 osub_14079C5C0 = (sub_14079C5C0)(moddingApi::Memory::moduleBase + 0x79B9C0 + 0xC00);

	typedef __int64(__fastcall* sub_1406C5A60) (__int64 a1);
	sub_1406C5A60 osub_1406C5A60 = (sub_1406C5A60)(moddingApi::Memory::moduleBase + 0x6C4E60 + 0xC00);

	typedef __int64(__fastcall* sub_14073CB48) (__int64 a1, int a2);
	sub_14073CB48 osub_14073CB48 = (sub_14073CB48)(moddingApi::Memory::moduleBase + 0x73BF48 + 0xC00);

	typedef __int64(__fastcall* sub_1407C8FB8) (__int64 a1, unsigned int a2);
	sub_1407C8FB8 osub_1407C8FB8 = (sub_1407C8FB8)(moddingApi::Memory::moduleBase + 0x7C83B8 + 0xC00);

	typedef int(__fastcall* sub_1407ADF88) (__int64 a1);
	sub_1407ADF88 osub_1407ADF88 = (sub_1407ADF88)(moddingApi::Memory::moduleBase + 0x7AD388 + 0xC00);

	typedef __int64(__fastcall* sub_14079BB7C) (__int64 a1);
	sub_14079BB7C osub_14079BB7C = (sub_14079BB7C)(moddingApi::Memory::moduleBase + 0x7A9F7C + 0xC00);

	typedef __int64(__fastcall* sub_14077DA68) (__int64 a1, int a2, __int64 a3);
	sub_14077DA68 osub_14077DA68 = (sub_14077DA68)(moddingApi::Memory::moduleBase + 0x77CE68 + 0xC00);

	typedef __int64(__fastcall* sub_140A046F0) (__int64 a1);
	sub_140A046F0 osub_140A046F0 = (sub_140A046F0)(moddingApi::Memory::moduleBase + 0xA03AF0 + 0xC00);

	typedef __int64(__fastcall* sub_1407C0FAC) (__int64 a1);
	sub_1407C0FAC osub_1407C0FAC = (sub_1407C0FAC)(moddingApi::Memory::moduleBase + 0x7C03AC + 0xC00);

	v2 = a1 + 0x218;
	v3 = a1;
	if (((*(DWORD*)(v3 + 0xCC0) == 10) || (*(DWORD*)(v3 + 0xCC0) == 11) || (*(DWORD*)(v3 + 0xCC0) == 12)) && (osub_1407C0FAC(v2) || (unsigned int)osub_1407C0DD8(v2, 12))) //|| ((*(DWORD*)(v3 + 0xCC0) == 10) || (*(DWORD*)(v3 + 0xCC0) == 11) || (*(DWORD*)(v3 + 0xCC0) == 12))
	{
		v18 = 0;
		if (*(BYTE*)(v3 + 85464) & 0x20) {
			v18 = 1;
		}
		v19 = osub_14077DA68(v3, 247, 1i64) == 0;
		v21 = 123;
		if (v19) {
			v21 = 72;
		}
		if (v18)
		{
			*(DWORD*)(v3 + 0xCC8) = v21;
			*(DWORD*)(v3 + 0xCDC) = 1;
			*(DWORD*)(v3 + 0x14DD8) = 0;
		}
		else
		{
			*(DWORD*)(v3 + 0xCC8) = v21;
			*(DWORD*)(v3 + 0xCDC) = 1;
		}
		result = (*(int(__fastcall**)(__int64))(*(__int64*)v3 + 0x1728i64))(v3);
		if (result)
			result = (*(int(__fastcall**)(__int64, signed __int64, __int64, signed __int64))(*(__int64*)v3 + 0xDE0i64))(
				v3,
				153i64,
				0i64,
				1i64);
		return result;
	}
	else {
		return oSetGrabPlayerState(a1, a2);
	}
	/*
	if ((unsigned int)osub_1407C0DD8(a1 + 0x218, 0))
		osub_140792ECC(v3);
	if ((*(int(__fastcall**)(__int64))(*(__int64*)v3 + 3720i64))(v3)
		&& (osub_1407C0C8C(v2) || (unsigned int)osub_1407C0DD8(v2, 2)))
	{
		(*(void (**)(void))(**(__int64**)(v3 + 86328) + 16i64))();
		if ((*(int(__fastcall**)(__int64))(*(__int64*)v3 + 3328i64))(v3) || *(DWORD*)(v3 + 65140) < 1)
		{
			if (*(BYTE*)(v3 + 85464) & 8)
				osub_1407A3E24(v3, *(DWORD*)(v3 + 0x141EC) == 0);
			else
				osub_1407E0EC0(1, v3, a2);
		}
		else
		{
			if ((*(int(__fastcall**)(__int64))(*(__int64*)v3 + 4008i64))(v3))
			{
				osub_1407DF5AC(v3, a2);
				osub_1407E10A0(v3, 4141i64);
			}
			osub_140784628(v3, 1i64);
		}
	}
	if (sub_1407AC910(v3) && (*(int(__fastcall**)(__int64))(*(__int64*)v3 + 0xE80i64))(v3))
		(*(void(__fastcall**)(__int64, signed __int64))(*(__int64*)v3 + 0xDA8i64))(v3, 13i64);
	if (osub_1407C0C8C(v2))
	{
		if ((unsigned int)(*(DWORD*)(v3 + 3264) - 4) > 1)
		{
			if (*(BYTE*)(v3 + 85464) & 4)
			{
			LABEL_22:
				osub_140792ECC(v3);
				goto LABEL_23;
			}
		}
		else
		{
			osub_1407C0748(v2, 0i64);
			if (a2 > 0.5)
				goto LABEL_22;
		}
	}
LABEL_23:
	if ((*(int(__fastcall**)(__int64))(*(__int64*)v3 + 4536i64))(v3)
		|| !(unsigned int)osub_1407C09D8(v2) && !(unsigned int)osub_1407C0DD8(v2, 7) && !(unsigned int)osub_1407C0DD8(v2, 39))
	{
		goto LABEL_49;
	}
	v4 = 0;
	if (sub_14079C5C0(v3) && *(__int64*)(v3 + 4176))
	{
		if (*(DWORD*)(v3 + 65140) == 3)
			v4 = 1;
		if (osub_1406C5A60(v3))
			v4 = 1;
	}
	if (!(*(int(__fastcall**)(__int64, __int64, __int64))(*(__int64*)v3 + 3824i64))(v3, 0i64, (unsigned int)v4))
	{
		if (!(*(int(__fastcall**)(__int64, __int64))(*(__int64*)v3 + 6000i64))(v3, 0i64))
			goto LABEL_49;
		*(DWORD*)(v3 + 84752) = 1;
		*(DWORD*)(v3 + 84756) = 1;
		osub_14073CB48(moddingApi::Memory::GetQword(141610160), 4104i64, 0i64, 1i64);
	}
	v5 = 135;
	if (osub_1407C8FB8(v3, 0i64))
	{
		if (!(unsigned int)osub_1407C0DD8(v2, 7))
		{
			(*(void(__fastcall**)(__int64))(*(__int64*)v3 + 3432i64))(v3);
			if (a2 >= 100.0)
				v5 = 141;
		}
	}
	if (!(*(int(__fastcall**)(__int64))(*(__int64*)v3 + 4944i64))(v3))
	{
	LABEL_45:
		v6 = (unsigned int)v5;
		goto LABEL_46;
	}
	if (!(unsigned int)osub_1407C0DD8(v2, 39) || v5 != 141)
	{
		if (!(unsigned int)osub_1407C0DD8(v2, 7))
			goto LABEL_47;
		goto LABEL_45;
	}
	v6 = 141i64;
LABEL_46:
	(*(void(__fastcall**)(__int64, signed __int64))(*(__int64*)v3 + 3496i64))(v3, v6);
LABEL_47:
	if (*(DWORD*)(v3 + 85464) & 0x100)
		*(DWORD*)(v3 + 85464) = 0;
LABEL_49:
	if ((unsigned int)osub_1407C09D8(v2) || (unsigned int)osub_1407C0DD8(v2, 6))
	{
		if (osub_1407ADF88(v3))
		{
			v7 = 466;
			v8 = osub_14079BB7C(v3);
			if (v8)
			{
				v9 = v8 - 1;
				if (v9)
				{
					v10 = v9 - 1;
					if (v10)
					{
						v11 = v10 - 1;
						if (v11)
						{
							v12 = v11 - 1;
							if (v12)
							{
								if (v12 == 1)
									v7 = 676;
							}
							else
							{
								v7 = 634;
							}
						}
						else
						{
							v7 = 592;
						}
					}
					else
					{
						v7 = 550;
					}
				}
				else
				{
					v7 = 508;
				}
			}
			DWORD(v13) = osub_14077DA68(v3, (unsigned int)v7, 1i64);
			v14 = 0;
			v15 = 0;
			if (v13)
				v14 = 1;
			osub_140A046F0(v37);
			(*(void(__fastcall**)(__int64, char*, const char*))(*(__int64*)v3 + 3168i64))(v3, &v37, "r foot");
			if (!*(DWORD*)(v3 + 82412) || osub_140756F5C(v3) && (a2 = v38, v38 > (float)(*(float*)(v3 + 120) + 50.0)))
				v15 = 1;
			v16 = 0;
			if (*(BYTE*)(v3 + 85464) & 0x40)
			{
				v16 = 1;
				*(DWORD*)(v3 + 85464) = 0;
			}
			if (*(DWORD*)(v3 + 85192))
			{
				DWORD(v17) = (*(int(__fastcall**)(__int64))(*(__int64*)v3 + 3464i64))(v3);
				if (!v17 || !*(DWORD*)(v17 + 85192))
				{
					(*(void(__fastcall**)(__int64, __int64))(*(__int64*)v3 + 3640i64))(v3, (unsigned int)v16);
					goto LABEL_82;
				}
			LABEL_78:
				osub_1407C2EEC(v3, (unsigned int)v16);
				goto LABEL_82;
			}
			if (!v15)
				goto LABEL_78;
			if (v14)
				osub_1407C2E9C(v3, (unsigned int)v16);
		}
		else if (!(*(int(__fastcall**)(__int64))(*(__int64*)v3 + 0xD08i64))(v3) && *(DWORD*)(v3 + 65140) == 1)
		{
			osub_1407E10A0(v3, 4141i64);
			(*(void(__fastcall**)(__int64))(*(__int64*)v3 + 3312i64))(v3);
			osub_1407DF5AC(v3, a2);
			osub_140784628(v3, 1i64);
		}
	}
LABEL_82:
	if ((*(int(__fastcall**)(__int64))(*(__int64*)v3 + 3688i64))(v3)
		&& (osub_1407C0C8C(v2) || (unsigned int)osub_1407C0DD8(v2, 20)))
	{
		if (*(DWORD*)(v3 + 82412))
		{
			v18 = 0i64;
			if (*(BYTE*)(v3 + 85464) & 2)
			{
				v18 = 1i64;
				*(DWORD*)(v3 + 85464) = 0;
			}
			(*(void(__fastcall**)(__int64, signed __int64))(*(__int64*)v3 + 3624i64))(v3, v18);
		}
		else if ((*(int(__fastcall**)(__int64))(*(__int64*)v3 + 3840i64))(v3))
		{
			(*(void(__fastcall**)(__int64))(*(__int64*)v3 + 0xE30i64))(v3);
		}
	}
	if ((*(int(__fastcall**)(__int64))(*(__int64*)v3 + 3760i64))(v3)
		&& (osub_1407C0FAC(v2) || (unsigned int)osub_1407C0DD8(v2, 12)))
	{
		v19 = 0;
		if (*(BYTE*)(v3 + 85464) & 0x20)
			v19 = 1;
		DWORD(v20) = osub_14077DA68(v3, 247i64, 1i64);
		v21 = v20 == 0;
		v22 = *(__int64*)v3;
		v23 = 123i64;
		if (v21)
			v23 = 72i64;
		if (v19)
		{
			(*(void(__fastcall**)(__int64, signed __int64, __int64, __int64))(v22 + 0xDE0))(v3, v23, 0i64, 0i64);
			*(DWORD*)(v3 + 85464) = 0;
		}
		else
		{
			(*(void(__fastcall**)(__int64, signed __int64, __int64, signed __int64))(v22 + 0xDE0))(v3, v23, 0i64, 1i64);// Write a grab state
		}
	}
	if ((*(int(__fastcall**)(__int64))(*(__int64*)v3 + 0xEF8i64))(v3))
	{
		v24 = (*(int (**)(void))(**(__int64**)(v3 + 86400) + 24i64))();
		a2 = (float)*((BYTE*)qword_1416663C8 + 2370);
		if (osub_1407C0770(v2) >= (signed int)ffloor((float)v24 / (float)(30.0 / a2)) || (unsigned int)osub_1407C0DD8(v2, 4))
		{
			v25 = osub_1407DAEC8(v3);
			v26 = 133i64;
			if (!v25)
				v26 = 132i64;
			(*(void(__fastcall**)(__int64, signed __int64, __int64, signed __int64))(*(__int64*)v3 + 3552i64))(
				v3,
				v26,
				0i64,
				1i64);
		}
	}
	(*(void(__fastcall**)(__int64))(*(__int64*)v3 + 3664i64))(v3);
	v27 = -1;
	if (osub_1407C0C44(v2) || (unsigned int)osub_1407C0DD8(v2, 14))
	{
		v27 = 2;
	}
	else if (osub_1407C0C74(v2) || (unsigned int)osub_1407C0DD8(v2, 15))
	{
		v27 = 0;
	}
	else if (osub_1407C0C5C(v2) || (unsigned int)osub_1407C0DD8(v2, 16))
	{
		v27 = 3;
	}
	else if (osub_1407C0C2C(v2) || (unsigned int)osub_1407C0DD8(v2, 17))
	{
		v27 = 1;
	}
	if (osub_1406C3880(v3))
		*(DWORD*)(v3 + 87636) = v27;
	else
		osub_1407E15F4(v3, (unsigned int)v27);
	if (osub_1407C0AF8(v2) || (unsigned int)osub_1407C0DD8(v2, 13) || (unsigned int)osub_1407C0DD8(v2, 3))
	{
		if (!*(DWORD*)(v3 + 82412))
			goto LABEL_179;
		if ((*(int(__fastcall**)(__int64, signed __int64))(*(__int64*)v3 + 3792i64))(v3, 1i64))
			goto LABEL_129;
		if (!*(DWORD*)(v3 + 82412))
		{
		LABEL_179:
			if ((*(int(__fastcall**)(__int64, signed __int64))(*(__int64*)v3 + 3800i64))(v3, 1i64))
			{
			LABEL_129:
				v28 = *(__int64*)v3;
				v29 = v3;
				if (*(DWORD*)(v3 + 82412))
					v30 = 70i64;
				else
					v30 = 71i64;
				goto LABEL_139;
			}
		}
		(*(void (**)(void))(**(__int64**)(v3 + 86352) + 16i64))();
		if ((*(int(__fastcall**)(__int64))(*(__int64*)v3 + 3328i64))(v3) || *(DWORD*)(v3 + 65140) < 1)
		{
			if ((*(int(__fastcall**)(__int64))(*(__int64*)v3 + 3768i64))(v3))
			{
				v28 = *(__int64*)v3;
				v30 = 67i64;
				v29 = v3;
			LABEL_139:
				(*(void(__fastcall**)(__int64, signed __int64, __int64, signed __int64))(v28 + 3552))(v29, v30, 0i64, 1i64);
				goto LABEL_140;
			}
		}
		else
		{
			if ((*(int(__fastcall**)(__int64))(*(__int64*)v3 + 4008i64))(v3))
			{
				osub_1407DF5AC(v3, a2);
				osub_1407E10A0(v3, 4141i64);
			}
			osub_140784628(v3, 1i64);
		}
	}
LABEL_140:
	if ((*(int(__fastcall**)(__int64))(*(__int64*)v3 + 3736i64))(v3)
		&& (osub_1407C0B7C(v2) || (unsigned int)osub_1407C0DD8(v2, 18)))
	{
		if (*(DWORD*)(v3 + 0xC8C) == 114)
			osub_1407984F8(v3, 4492i64, 4294966096i64);
		v31 = osub_140756F5C(v3);
		v32 = v3;
		if (!v31)
		{
			v33 = 1i64;
			goto LABEL_149;
		}
		if (!osub_1407ABEFC(v3))
		{
			v33 = 0i64;
			v32 = v3;
		LABEL_149:
			(*(void(__fastcall**)(__int64, signed __int64, __int64, signed __int64))(*(__int64*)v3 + 3552i64))(
				v32,
				73i64,
				0i64,
				v33);
			goto LABEL_150;
		}
	}
LABEL_150:
	if ((unsigned int)osub_1407C0B64(v2))
	{
		osub_1407C0748(v2, 0i64);
		if (a2 > 0.5 && !osub_14079C53C(v3))
			osub_140792ECC(v3);
	}
	if ((*(int(__fastcall**)(__int64))(*(__int64*)v3 + 3680i64))(v3))
	{
		osub_1407C0748(v2, 0i64);
		if (a2 > 0.1)
		{
			if (!osub_140756F5C(v3))
			{
				if (!(*(BYTE*)(v3 + 0x14DD8) & 1))
				{
					v34 = 1i64;
					goto LABEL_161;
				}
			LABEL_158:
				v34 = 0i64;
			LABEL_161:
				(*(void(__fastcall**)(__int64, signed __int64, __int64, signed __int64))(*(__int64*)v3 + 0xDE0i64))(
					v3,
					2i64,
					0i64,
					v34);
				goto LABEL_162;
			}
			if (!osub_1407ABEFC(v3))
				goto LABEL_158;
		}
	}
LABEL_162:
	v35 = 1;
	osub_14057647C(v3);
	if ((*(int(__fastcall**)(__int64))(*(__int64*)v3 + 5784i64))(v3)
		&& (*(int(__fastcall**)(__int64))(*(__int64*)v3 + 5776i64))(v3))
	{
		if ((*(int(__fastcall**)(__int64, __int64))(*(__int64*)v3 + 5792i64))(v3, *(DWORD*)(v3 + 87864)))
		{
			(*(void(__fastcall**)(__int64))(*(__int64*)v3 + 5808i64))(v3);
			v35 = 0;
		}
		else if (osub_1407C09A8(v2, 1i64) && (*(int(__fastcall**)(__int64))(*(__int64*)v3 + 4008i64))(v3))
		{
			osub_1407E10A0(v3, 4141i64);
			osub_140798668(v3, 4141i64);
		}
	}
	if (*(DWORD*)(v3 + 87880))
		v35 = 0;
	if (v35)
		(*(void(__fastcall**)(__int64))(*(__int64*)v3 + 5992i64))(v3);
	(*(void(__fastcall**)(__int64))(*(__int64*)v3 + 5832i64))(v3);
	if (*(DWORD*)(v3 + 87592))
		(*(void(__fastcall**)(__int64))(*(__int64*)v3 + 0xD68i64))(v3);
	result = (*(int(__fastcall**)(__int64))(*(__int64*)v3 + 0x1728i64))(v3);
	if (result)
		result = (*(int(__fastcall**)(__int64, signed __int64, __int64, signed __int64))(*(__int64*)v3 + 0xDE0i64))(
			v3,
			153i64,
			0i64,
			1i64);
	return result;
}
*/
}

typedef int(__fastcall* decideItemState) (__int64 a1, unsigned int a2);
decideItemState oDecideItemState = NULL;

int nDecideItemState(__int64 a1, unsigned int a2) {
	__int64 playerAddr; // r14@1
	int playerState; // ecx@1
	int v4; // ebp@1
	signed int v5; // ebx@1
	unsigned __int64 v6; // rcx@3
	signed __int64 v7; // rax@4
	signed int v8; // edx@6
	unsigned __int64 v9; // rax@6
	__int64 v10; // rdi@9
	__int64 v11; // esi@9
	__int64 v12; // er15@9
	__int64 v13; // rbx@9
	int v14; // eax@9
	__int64 v15; // eax@9
	__int64 v16; // rcx@13
	signed __int64 v17; // rcx@20


	typedef int(__fastcall* sub_140529598) (__int64 a1);
	sub_140529598 osub_140529598 = (sub_140529598)(moddingApi::Memory::moduleBase + 0x528998 + 0xC00);

	typedef __int64(__fastcall* sub_14074B034) (__int64 a1, __int64 a2, int a3);
	sub_14074B034 osub_14074B034 = (sub_14074B034)(moddingApi::Memory::moduleBase + 0x74A434 + 0xC00);

	typedef int(__fastcall* sub_14079C5C0) (__int64 a1);
	sub_14079C5C0 osub_14079C5C0 = (sub_14079C5C0)(moddingApi::Memory::moduleBase + 0x79B9C0 + 0xC00);

	typedef int(__fastcall* sub_1407ED2B4) (__int64 a1);
	sub_1407ED2B4 osub_1407ED2B4 = (sub_1407ED2B4)(moddingApi::Memory::moduleBase + 0x7EC6B4 + 0xC00);

	typedef int(__fastcall* sub_1407E10D4) (__int64 a1);
	sub_1407E10D4 osub_1407E10D4 = (sub_1407E10D4)(moddingApi::Memory::moduleBase + 0x7E04D4 + 0xC00);

	playerAddr = a1;
	playerState = *(DWORD*)(a1 + 0xCC0);
	v4 = a2;
	v5 = 1;
	if ((unsigned int)(playerState - 73) <= 3
		|| playerState == 92
		|| (v6 = (unsigned int)(playerState - 204), (unsigned int)v6 <= 0x30)
		&& (v7 = 281474976710679i64, _bittest64(&v7, v6)))
	{
		v5 = 0;
	}
	v8 = (*(int(__fastcall**)(__int64, signed __int64))(*(__int64*)playerAddr + 0x1398i64))(playerAddr, 17i64) != 0 ? v5 : 0;
	v9 = -*(DWORD*)(playerAddr + 0x14B30);
	if (((*(DWORD*)(playerAddr + 0x14B30) != 0 ? v8 : 0) && v4 != -1) || (*(DWORD*)(playerAddr + 0xCC0) == 73)) //State Checking + If item slot is available
	{
		DWORD(v9) = (*(int(__fastcall**)(__int64, __int64))(*(__int64*)playerAddr + 0x1758i64))(
			playerAddr,
			(unsigned int)v4);
		if ((DWORD)v9)
		{
			v10 = moddingApi::Memory::moduleBase + 0x14161C8C8 - 0x140000000 + 0xC00;
			v11 = osub_140529598((__int64)"BATTLE_ITEM150");// gb pill
			v12 = osub_140529598((__int64)"BATTLE_ITEM192");
			v13 = (*(int(__fastcall**)(__int64))(*(__int64*)playerAddr + 64i64))(playerAddr);
			v14 = (*(int (**)(void))(*(__int64*)(playerAddr + 0xB00) + 32i64))();
			v15 = osub_14074B034(104 * v13 + v10 + 24, (unsigned int)v14, v4);
			if (v11 != v15 && v12 != v15)         // if it's not a gb pill&& v12 == v15
			{
				DWORD(v9) = (*(int(__fastcall**)(__int64, __int64))(*(__int64*)playerAddr + 0x1760i64))(
					playerAddr,
					(unsigned int)v4);      // calls setitemplayerstate
				return v9;
			}
			*(DWORD*)(playerAddr + 87548) = v4;
			if (!osub_14079C5C0(playerAddr))
			{
				DWORD(v9) = (*(int(__fastcall**)(__int64, signed __int64, __int64, signed __int64))(*(__int64*)playerAddr
					+ 0xDE0i64))(// calls setPlayerState with a gb pill parameter
						playerAddr,
						155i64,
						0i64,
						1i64);
				return v9;
			}
			v16 = *(__int64*)(playerAddr + 4176);
			if (!v16 || !osub_1407ED2B4(v16))
			{
				DWORD(v9) = (*(int(__fastcall**)(__int64, signed __int64, __int64, signed __int64))(*(__int64*)playerAddr
					+ 0xDE0i64))(
						playerAddr,
						156i64,
						0i64,
						1i64);
				if ((DWORD)v9)
					DWORD(v9) = (*(int(__fastcall**)(__int64, signed __int64))(**(__int64**)(playerAddr + 4176) + 3496i64))(
						*(__int64*)(playerAddr + 4176),
						99i64);
				return v9;
			}
		LABEL_22:
			DWORD(v9) = osub_1407E10D4(playerAddr);
			return v9;
		}
		if (!*(DWORD*)(playerAddr + 3260))
		{
			v9 = (unsigned int)(*(DWORD*)(playerAddr + 3264) - 81);
			if ((unsigned int)v9 > 0x38 || (v17 = 72066390130950145i64, !_bittest64(&v17, v9)))
			{
				DWORD(v9) = (*(int(__fastcall**)(__int64))(*(__int64*)playerAddr + 5720i64))(playerAddr);
				if ((DWORD)v9)
					goto LABEL_22;
			}
		}
	}
	return v9;
}

typedef __int64(__fastcall* SingleMoveBuffering) (__int64 a1, unsigned int a2);
SingleMoveBuffering oSingleMoveBuffering = NULL;

__int64 nSingleMoveBuffering(__int64 a1, unsigned int a2) {
	__int64 v2; // r8@1
	signed __int64 v3; // rdx@1
	__int64 v4; // rbx@1
	signed int v5; // edi@1
	signed int v6; // esi@13
	__int64 v7; // r8@21
	int v8; // eax@22
	unsigned int v9; // ecx@22
	unsigned int v10; // eax@22
	__int64 v11; // r8@25
	__int64 v12; // rdx@25
	__int64 v14; // [sp+20h] [bp-18h]@0


	typedef __int64(__fastcall* sub_14077DA68) (__int64 a1, int a2, __int64 a3);
	sub_14077DA68 osub_14077DA68 = (sub_14077DA68)(moddingApi::Memory::moduleBase + 0x77CE68 + 0xC00);

	typedef void(__fastcall* sub_1407825B8) (__int64 a1, __int64 a2);
	sub_1407825B8 osub_1407825B8 = (sub_1407825B8)(moddingApi::Memory::moduleBase + 0x7819B8 + 0xC00);

	typedef int(__fastcall* sub_140781860) (__int64 a1);
	sub_140781860 osub_140781860 = (sub_140781860)(moddingApi::Memory::moduleBase + 0x780C60 + 0xC00);

	typedef int(__fastcall* sub_14077E64C) (__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5, unsigned int a6);
	sub_14077E64C osub_14077E64C = (sub_14077E64C)(moddingApi::Memory::moduleBase + 0x77DA4C + 0xC00);

	typedef int(__fastcall* sub_140781414) (__int64 a1, __int64 a2, int a3);
	sub_140781414 osub_140781414 = (sub_140781414)(moddingApi::Memory::moduleBase + 0x780814 + 0xC00);

	typedef int(__fastcall* sub_140790E38) (__int64 a1, int a2);
	sub_140790E38 osub_140790E38 = (sub_140790E38)(moddingApi::Memory::moduleBase + 0x790238 + 0xC00);

	typedef int(__fastcall* sub_1407C2EEC) (__int64 a1, unsigned int a2);
	sub_1407C2EEC osub_1407C2EEC = (sub_1407C2EEC)(moddingApi::Memory::moduleBase + 0x7C22EC + 0xC00);

	typedef int(__fastcall* sub_1406B5D14) (__int64 a1, int a2, signed int a3);
	sub_1406B5D14 osub_1406B5D14 = (sub_1406B5D14)(moddingApi::Memory::moduleBase + 0x6B5114 + 0xC00);

	typedef int(__fastcall* sub_1407C2E9C) (__int64 a1, unsigned int a2);
	sub_1407C2E9C osub_1407C2E9C = (sub_1407C2E9C)(moddingApi::Memory::moduleBase + 0x7C229C + 0xC00);

	typedef int(__fastcall* sub_140794B08) (__int64 a1);
	sub_140794B08 osub_140794B08 = (sub_140794B08)(moddingApi::Memory::moduleBase + 0x793F08 + 0xC00);


	v2 = a2;
	v3 = *(DWORD*)(a1 + 0x14104);
	v4 = a1;
	v5 = 0;
	std::cout << "running" << std::endl;
	if ((DWORD)v3 == 16)
	{
		v3 = 16i64;
		goto LABEL_31;
	}

	if (!(DWORD)v3)
		goto LABEL_33;
	

	if ((DWORD)v3 == 63)
	{
		if (*(DWORD*)(a1 + 0xCC0) == 66)
		{
			std::cout << "if (*(DWORD*)(a1 + 0xCC0) == 66)" << std::endl;
			(*(void(__fastcall**)(__int64, signed __int64, __int64))(*(__int64*)a1 + 0xDA8i64))(a1, 63i64, v2);
			v5 = 1;
			osub_1407825B8(v4, 0xFFFFFFFFi64);
			osub_140781860(v4);
			v12 = *(DWORD*)(v4 + 0x14108);
			if ((DWORD)v12 != 74)
			{
				std::cout << "((DWORD)v12 != 74)" << std::endl;
				DWORD(v14) = 0;
				osub_14077E64C(v4, v12, v11, 0xFFFFFFFFi64, v14, 0);
			}
			goto LABEL_33;
		}
			if (osub_140781414(a1, *(DWORD*)(a1 + 0x14108), v2)
				&& (*(int(__fastcall**)(__int64, __int64))(*(__int64*)v4 + 0xE48i64))(v4, *(DWORD*)(v4 + 0x14108)))// setJumpState2PlayerState
			{
				*(DWORD*)(v4 + 0x14108) = 74;
				osub_1407825B8(v4, 0xFFFFFFFFi64);
				*(__int64*)(v4 + 0x164) = 0i64;
				osub_140790E38(v4, 0i64);
				*(DWORD*)(v4 + 364) = 0;
				goto LABEL_23;
			}
		}
		else
		{
			if ((DWORD)v3 != 66)
			{
				std::cout << "((DWORD)v3 != 66)" << std::endl;
				if ((DWORD)v3 == 72)
				{
					std::cout << "((DWORD)v3 == 72)" << std::endl;
					if (*(DWORD*)(a1 + 0xCC0) == 66)
						goto LABEL_33;
					v6 = 1;
					if ((*(int(__fastcall**)(__int64, signed __int64, __int64))(*(__int64*)a1 + 0x11B8i64))(a1, v3, v2)
						&& osub_14077DA68(v4, 247, 1i64))
					{
						std::cout << "((*(int(__fastcall**)(__int64, signed __int64, __int64))(*(__int64*)a1 + 0x11B8i64))(a1, v3, v2) && osub_14077DA68(v4, 247, 1i64))" << std::endl;
						v6 = 0;
					}
					if (*(DWORD*)(v4 + 3260) && osub_14077DA68(v4, 247, 1i64))
						std::cout << "(*(DWORD*)(v4 + 3260) && osub_14077DA68(v4, 247, 1i64))" << std::endl;
						v6 = 0;
						if (!v6)
							std::cout << "!v6" << std::endl;
						goto LABEL_33;
					v3 = *(DWORD*)(v4 + 82180);
				}
				else
				{
					if ((DWORD)v3 == 77)
					{
						if (*(DWORD*)(a1 + 3264) != 66)
						{
							osub_1407C2EEC(a1, 1u);
							goto LABEL_32;
						}
					LABEL_33:
						std::cout << "label 33" << std::endl;
						std::cout << v3 << std::endl;
						if (((*(DWORD*)(a1 + 0xCC0) == 66) || (*(DWORD*)(a1 + 0xCC0) == 63)) && (v3 == 0)) {
							*(DWORD*)(a1 + 0xCC8) = 67;
							*(DWORD*)(a1 + 0xCDC) = 1;
						}
						osub_1406B5D14(*(__int64*)(v4 + 0xFD90), 16, 10);
						return (unsigned int)v5;
					}
					if ((DWORD)v3 == 78)
					{
						if (*(DWORD*)(a1 + 0xCC0) != 66)
						{
							osub_1407C2E9C(a1, 1i64);
						LABEL_32:
							std::cout << "label 32" << std::endl;
							v5 = 1;
							goto LABEL_33;
						}
						goto LABEL_33;
					}
				}
			LABEL_31:
				std::cout << "label 31" << std::endl;
				(*(void(__fastcall**)(__int64, signed __int64, __int64))(*(__int64*)v4 + 3496i64))(v4, v3, v2);
				if (((*(DWORD*)(a1 + 0xCC0) == 66) && (((v3 == 4) || (v3 == 5) || (v3 == 10) || (v3 == 11) || (v3 == 12))))) {
					*(DWORD*)(a1 + 0xCC8) = v3;
					*(DWORD*)(a1 + 0xCDC) = 1;
				}
				goto LABEL_32;
			}
			if (osub_140781414(a1, *(DWORD*)(a1 + 0x14108), 0))
			{
				DWORD(v14) = 0;
				osub_14077E64C(v4, *(DWORD*)(v4 + 0x14108), v7, 0xFFFFFFFFi64, v14, 0);
				*(DWORD*)(v4 + 0x14108) = 74;
				osub_140794B08(v4);
				++* (DWORD*)(v4 + 82172);
				*(DWORD*)(v4 + 82176) = 0;
				v8 = *(DWORD*)(v4 + 3264);
				*(DWORD*)(v4 + 0xCCC) = 0;
				*(DWORD*)(v4 + 0xCC0) = 66;
				*(DWORD*)(v4 + 0xCC4) = v8;
				v9 = *((BYTE*)(moddingApi::Memory::moduleBase + 0x1416663C8 - 0x1416663C8 + 0xC00) + 2370);
				*(DWORD*)(v4 + 3272) = 0;
				v10 = -(0xBB8 / v9);
				*(DWORD*)(v4 + 3292) = 0;
				*(DWORD*)(v4 + 3280) = v10;
				*(DWORD*)(v4 + 3284) = v10;
				osub_1407825B8(v4, 0xFFFFFFFFi64);
			LABEL_23:
				std::cout << "label 23" << std::endl;
				osub_140781860(v4);
				return (unsigned int)v5;
			}
		}
		return (unsigned int)v5;
	}

signed typedef __int64(__fastcall* areYouComboing) (__int64 a1, unsigned int a2, unsigned int a3);
areYouComboing oAreYouComboing = NULL;


signed __int64 nAreYouComboing(__int64 a1, unsigned int playerState, unsigned int a3) {
	return oAreYouComboing(a1, playerState, a3);
}

	//Initializes our memory hooks through usage of the MinHook library. uintptr_t addresses MUST be local variables.
void moddingApi::Memory::InitHooks() {
	if (MH_Initialize() == MH_OK) {
		//bool status;
		std::uintptr_t addrLoadCpkInit = (std::uintptr_t)(moddingApi::Memory::moduleBase + 0x854F3C + 0xC00);
		std::uintptr_t addrNewPlayerState = (std::uintptr_t)(moddingApi::Memory::moduleBase + 0x7ADCB4 + 0xC00);
		std::uintptr_t addrMessageInfo = (std::uintptr_t)(moddingApi::Memory::moduleBase + 0xAB8720 + 0xC00);
		std::uintptr_t addrMemString = (std::uintptr_t)(moddingApi::Memory::moduleBase + 0xA01230 + 0xC00);
		std::uintptr_t addrInitializeccSceneFreeBattleBegin = (std::uintptr_t)(moddingApi::Memory::moduleBase + 0x6DCC64 + 0xC00);
		std::uintptr_t addrPlayerAnim = (std::uintptr_t)(moddingApi::Memory::moduleBase + 0x77D8A0 + 0xC00);
		std::uintptr_t addrSetNoChakraCirclePlayerState = (std::uintptr_t)(moddingApi::Memory::moduleBase + 0x22A208 + 0xC00);
		std::uintptr_t addrSetGrabPlayerState = (std::uintptr_t)(moddingApi::Memory::moduleBase + 0x7DF614 + 0xC00);
		std::uintptr_t addrDecideItemState = (std::uintptr_t)(moddingApi::Memory::moduleBase + 0x7E09F4 + 0xC00);
		std::uintptr_t addrSingleMoveBuffering = (std::uintptr_t)(moddingApi::Memory::moduleBase + 0x77EF30 + 0xC00);
		std::uintptr_t addrAreYouComboing = (std::uintptr_t)(moddingApi::Memory::moduleBase + 0x7AD960 + 0xC00);
		std::cout << "MinHook Initialized" << std::endl;
		
		bool status = MH_CreateHook((LPVOID)addrAreYouComboing, nAreYouComboing, (LPVOID*)(&oAreYouComboing));
		if (status != MH_OK)
		{
			std::cout << "could not create hook PlayerAnim" << std::endl;
		}

		status = MH_EnableHook((LPVOID)addrAreYouComboing);
		if (status != MH_OK)
		{
			std::cout << "could not enable hook PlayerAnim" << std::endl;
		}

		 status = MH_CreateHook((LPVOID)addrSingleMoveBuffering, &nSingleMoveBuffering, reinterpret_cast<LPVOID*>(&oSingleMoveBuffering));
		if (status != MH_OK)
		{
			std::cout << "could not create hook PlayerAnim" << std::endl;
		}

		status = MH_EnableHook((LPVOID)addrSingleMoveBuffering);
		if (status != MH_OK)
		{
			std::cout << "could not enable hook PlayerAnim" << std::endl;
		}
		
		status = MH_CreateHook((LPVOID)addrDecideItemState, nDecideItemState, (LPVOID*)(&oDecideItemState));
		if (status != MH_OK)
		{
			std::cout << "could not create hook PlayerAnim" << std::endl;
		}

		status = MH_EnableHook((LPVOID)addrDecideItemState);
		if (status != MH_OK)
		{
			std::cout << "could not enable hook PlayerAnim" << std::endl;
		}

		status = MH_CreateHook((LPVOID)addrSetGrabPlayerState, nSetGrabPlayerState, (LPVOID*)(&oSetGrabPlayerState));
		if (status != MH_OK)
		{
			std::cout << "could not create hook PlayerAnim" << std::endl;
		}

		status = MH_EnableHook((LPVOID)addrSetGrabPlayerState);
		if (status != MH_OK)
		{
			std::cout << "could not enable hook PlayerAnim" << std::endl;
		}

		status = MH_CreateHook((LPVOID)addrPlayerAnim, nPlayerAnim, (LPVOID*)(&oPlayerAnim));
		if (status != MH_OK)
		{
			std::cout << "could not create hook PlayerAnim" << std::endl;
		}

		status = MH_EnableHook((LPVOID)addrPlayerAnim);
		if (status != MH_OK)
		{
			std::cout << "could not enable hook PlayerAnim" << std::endl;
		}

		status = MH_CreateHook((LPVOID)addrSetNoChakraCirclePlayerState, &nSetNoChakraCirclePlayerState, reinterpret_cast<LPVOID*>(&oSetNoChakraCirclePlayerState));
		if (status != MH_OK)
		{
			std::cout << "could not create hook PlayerAnim" << std::endl;
		}

		status = MH_EnableHook((LPVOID)addrSetNoChakraCirclePlayerState);
		if (status != MH_OK)
		{
			std::cout << "could not enable hook PlayerAnim" << std::endl;
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
		

		moddingApi::Scene::sceneHooks();


		
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



void moddingApi::Memory::WriteBytes() {
	//Set character limit to FFFF
	moddingApi::Memory::write_bytes<2>(moddingApi::Memory::moduleBase + 0x7220C2 + 0xC00, { 0xFF, 0xFF });
	moddingApi::Memory::write_bytes<2>(moddingApi::Memory::moduleBase + 0x7F3EB7 + 0xC00, { 0xFF, 0xFF });
	moddingApi::Memory::write_bytes<2>(moddingApi::Memory::moduleBase + 0x7F4139 + 0xC00, { 0xFF, 0xFF });
	moddingApi::Memory::write_bytes<2>(moddingApi::Memory::moduleBase + 0x8553DB + 0xC00, { 0xFF, 0xFF });
	
	//Disable online microphone for yourself and disable hearing your opponent's microphone
	moddingApi::Memory::write_bytes<3>(moddingApi::Memory::moduleBase + 0xB25794 + 0xC00, { 0x90, 0x90, 0x90 });
	moddingApi::Memory::write_bytes<3>(moddingApi::Memory::moduleBase + 0xB25966 + 0xC00, { 0x90, 0x90, 0x90 });
	moddingApi::Memory::write_bytes<5>(moddingApi::Memory::moduleBase + 0xB260B0 + 0xC00, { 0x90, 0x90, 0x90, 0x90, 0x90 });
	moddingApi::Memory::write_bytes<5>(moddingApi::Memory::moduleBase + 0xB26863 + 0xC00, { 0x90, 0x90, 0x90, 0x90, 0x90 });
	moddingApi::Memory::write_bytes<5>(moddingApi::Memory::moduleBase + 0xB26B45 + 0xC00, { 0x90, 0x90, 0x90, 0x90, 0x90 });
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