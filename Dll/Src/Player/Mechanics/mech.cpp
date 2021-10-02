#include "pch.hpp"

#include "mech.hpp"

#include "Player/IDs/id.hpp"

#include "imgui/include/imgui_impl_dx11.h"

#include <iostream>

//Toggles menu that controls 
//This function controls when the character can perform a shuriken. We've modified it so it can be performed out of a combo and tilt, like in Naruto Storm Revolution.
__int64 __fastcall mechanics::functions::canYouShuriken(__int64 a1) {
	if (!mechanics::enableShurikenComboTilt) {
	const auto retval = globals::hookManager->getOriginal<decltype(&mechanics::functions::canYouShuriken)>(mechanics::functions::canYouShuriken)(a1);
	return retval;
	}

	__int64 v1; // rbx@1
	signed int v2; // ecx@6
	__int64 result; // rax@10


	signed typedef __int64(__fastcall* sub_14076C79C) (__int64 a1);
	sub_14076C79C osub_14076C79C = (sub_14076C79C)(globals::moduleBase + 0x76BB9C + 0xC00);

	typedef __int64(__fastcall* sub_14077DA68) (__int64 a1, int a2, __int64 a3);
	sub_14077DA68 osub_14077DA68 = (sub_14077DA68)(globals::moduleBase + 0x77CE68 + 0xC00);

	v1 = a1;
	result = 0;
	if (*(DWORD*)(a1 + 0x14B30)) {
		if ((*(int(__fastcall**)(__int64, signed __int64))(*(__int64*)a1 + 0x1398i64))(a1, 6i64)) {
			if (!(unsigned int)osub_14076C79C(8i64)) {
				if (osub_14077DA68(v1, 151, 1i64)) {
					if (*(DWORD*)(v1 + 0x141EC)) {
						v2 = *(DWORD*)(v1 + 0xCC0);
						if (v2 > 0 && ((v2 <= 2 || v2 == 8 || v2 == 66 || v2 == 63)))
							result = 1;
					}
				}
			}
		}
	}
	return result;
}

//Function that runs when a new player state is written in memory. Modifications include: Resetting inputs on switch so supports do
//not perform charged jutsus, jutsu cancelling, and other unintended input-based mechanics. The shadow state of characters are removed
//on certain states to fix glitches such as the strike back shadow state glitch. mechanics::limboCloneAddr is used to fix the Six Paths Madara awakening action crash bug.
__int64 __fastcall mechanics::functions::newPlayerState(__int64 a1, unsigned int a2, int a3, int a4) {
	if (a2 == 211) {
		*(DWORD*)(a1 + 0xFE50) = 1;
		*(DWORD*)(a1 + 0xFE54) = 0;
		*(DWORD*)(a1 + 0xFE74) = 0;
		__int64 inputPointer = a1 + 0x218;
		*(DWORD*)(inputPointer + 0x404) = 0;
		*(DWORD*)(inputPointer + 0x408) = 0;
		*(DWORD*)(inputPointer + 0x40C) = 0;
	}
	if (a2 == 217) {
		*(DWORD*)(a1 + 0x14C60) = 0;
	}
	if (a2 == 1) {
		*(DWORD*)(a1 + 0x14C60) = 0;
	}
	if (*(DWORD*)(a1 + 0xC8C) == 0x72) //If character is Six Paths Madara
		mechanics::limboCloneAddr = a1;

	return globals::hookManager->callOriginal<decltype(&mechanics::functions::newPlayerState)>(mechanics::functions::newPlayerState, a1, a2, a3, a4);
}

//Sets a state with the right button with no other buttons held nor chakra loads. Modifications include NM tilt and GKunai Air Combo.
void mechanics::functions::setNoChakraCirclePlayerState(__int64 a1) {
	__int64 playerAddr; // rbx@1
	__int64 v2; // rbp@2
	signed int v3; // er14@2
	signed int v4; // edi@4
	signed int v5; // esi@4
	__int64 v6; // rax@11
	__int64 v7; // rax@23
	//Input Code

	playerAddr = a1;
	if (*(DWORD*)(playerAddr + 0xCC0) == 92 && (mechanics::enableTaunt))
		*(DWORD*)(playerAddr + 0xCC0) = 66;
	if (*(DWORD*)(a1 + 0xCC0) != 94)          // If the current state isn't 94
	{
		typedef __int64(__fastcall* sub_1407C0DD8) (__int64 a1, int a2);
		sub_1407C0DD8 osub_1407C0DD8 = (sub_1407C0DD8)(globals::moduleBase + 0x7C01D8 + 0xC00);

		typedef __int64(__fastcall* sub_1407C0A08) (__int64 a1);
		sub_1407C0A08 osub_1407C0A08 = (sub_1407C0A08)(globals::moduleBase + 0x7BFE08 + 0xC00);

		typedef __int64(__fastcall* sub_1407C09D8) (__int64 a1);
		sub_1407C09D8 osub_1407C09D8 = (sub_1407C09D8)(globals::moduleBase + 0x7BFDD8 + 0xC00);

		signed typedef __int64(__fastcall* sub_1407C0CE8) (__int64 a1, int a2);
		sub_1407C0CE8 osub_1407C0CE8 = (sub_1407C0CE8)(globals::moduleBase + 0x7C00E8 + 0xC00);
		v2 = a1 + 0x218;

		if ((*(DWORD*)(v2 + 0x404) == 1) && *(DWORD*)(playerAddr + 0xCC0) == 1 && (mechanics::enableTaunt)) {
			*(DWORD*)(playerAddr + 0xCC8) = 92;
			*(DWORD*)(playerAddr + 0xCDC) = 1;
		}

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
		if ((v3 || v4) && ((*(int(__fastcall**)(__int64))(*(__int64*)playerAddr + 0xEA8i64))(playerAddr) || (mechanics::enableGKunaiAirCombo &&(*(DWORD*)(playerAddr + 0xCC0) == 4 || *(DWORD*)(playerAddr + 0xCC0) == 5 || *(DWORD*)(playerAddr + 0xCC0) == 6)))) {
			v6 = *(__int64*)playerAddr;
			if (v5) {
				mechanics::functions::newPlayerState(playerAddr, 64, 0, 0);
				*(DWORD*)(playerAddr + 0x14DD8) = 0;
			}
			else {
				mechanics::functions::newPlayerState(playerAddr, 64, 0, 1);
			}
		}
		if ((((*(int(__fastcall**)(__int64, signed __int64))(*(__int64*)playerAddr + 0x1398i64))(playerAddr, 1i64)
			&& (((osub_1407C0CE8(v2, 0i64) && v4)) || (unsigned int)osub_1407C0DD8(v2, 9)))
			&& (((*(int(__fastcall**)(__int64))(*(__int64*)playerAddr + 0xEC8i64))(playerAddr)) || ((*(DWORD*)(playerAddr + 0xCC0) == 10) || (*(DWORD*)(playerAddr + 0xCC0) == 11) || (*(DWORD*)(playerAddr + 0xCC0) == 12))))) {
			if (!mechanics::enableNMTilt) {
				globals::hookManager->getOriginal<decltype(&mechanics::functions::setNoChakraCirclePlayerState)>(mechanics::functions::setNoChakraCirclePlayerState)(a1);
				return;
			}
				mechanics::functions::newPlayerState(playerAddr, 66, 0, 1);
		}
		if (v3 || v4) {
			if ((*(int(__fastcall**)(__int64, __int64))(*(__int64*)playerAddr + 0xEA0i64))(playerAddr, v5 == 0)) {
				v7 = *(__int64*)playerAddr;
				if (v5) {
					mechanics::functions::newPlayerState(playerAddr, 63, 0, 0);
					*(DWORD*)(playerAddr + 0x14DD8) = 0;
				}
				else {
					mechanics::functions::newPlayerState(playerAddr, 63, 0, 1);
				}
			}
		}
	}
	globals::hookManager->getOriginal<decltype(&mechanics::functions::setNoChakraCirclePlayerState)>(mechanics::functions::setNoChakraCirclePlayerState)(a1);
}

//This function sets new player animations. This function is also used to increase the animation speed of the startup of air chakra dashes.
__int64 __fastcall mechanics::functions::newPlayerAnim(__int64 rcx, int a1, __int64 a2, unsigned int a3, float a4, int a5, int a6) {
	globals::hookManager->getOriginal<decltype(&mechanics::functions::newPlayerAnim)>(mechanics::functions::newPlayerAnim)(rcx, a1, a2, a3, a4, a5, a6);
	if (mechanics::enableFastACD) {
	if (a1 == 37 && *(DWORD*)(rcx + 0xCC0) == 16) //If anim is ACD startup and player state is 16(CD + ACD)
		*(float*)(rcx + 0x1090) = 2.0f; //Set anim speed to 2.
	}
	return *(__int64*)(rcx + 0x208);
}

//This function sets multiple input player states such as grabs, and counters. Modifications are for NM Grab and for restoring GKunai.
__int64 __fastcall mechanics::functions::setMultiInputPlayerState(__int64 a1, float a2) {

	//return oSetGrabPlayerState(a1, a2);
	__int64 v2; // rbp@1
	__int64 v3; // rsi@1
	signed __int64 v18; // rdx@88
	signed int v19; // ebx@94
	__int64 v21;
	int result; // eax@175


	typedef __int64(__fastcall* sub_1407C0DD8) (__int64 a1, int a2);
	sub_1407C0DD8 osub_1407C0DD8 = (sub_1407C0DD8)(globals::moduleBase + 0x7C01D8 + 0xC00);

	typedef __int64(__fastcall* sub_14077DA68) (__int64 a1, int a2, __int64 a3);
	sub_14077DA68 osub_14077DA68 = (sub_14077DA68)(globals::moduleBase + 0x77CE68 + 0xC00);

	typedef __int64(__fastcall* sub_1407C0FAC) (__int64 a1);
	sub_1407C0FAC osub_1407C0FAC = (sub_1407C0FAC)(globals::moduleBase + 0x7C03AC + 0xC00);

	__int64 partnerAddr;
	v2 = a1 + 0x218;
	v3 = a1;
	if (((*(DWORD*)(v3 + 0xCC0) == 10) || (*(DWORD*)(v3 + 0xCC0) == 11) || (*(DWORD*)(v3 + 0xCC0) == 12)) && (osub_1407C0FAC(v2) || (unsigned int)osub_1407C0DD8(v2, 12))) { //|| ((*(DWORD*)(v3 + 0xCC0) == 10) || (*(DWORD*)(v3 + 0xCC0) == 11) || (*(DWORD*)(v3 + 0xCC0) == 12))
		v18 = 0;
		if (*(BYTE*)(v3 + 85464) & 0x20) {
			v18 = 1;
		}
		v19 = osub_14077DA68(v3, 247, 1i64) == 0;
		v21 = 123;
		if (v19) {
			v21 = 72;
		}
		if (v18) {
			*(DWORD*)(v3 + 0xCC8) = v21;
			*(DWORD*)(v3 + 0xCDC) = 1;
			*(DWORD*)(v3 + 0x14DD8) = 0;
		}
		else {
			*(DWORD*)(v3 + 0xCC8) = v21;
			*(DWORD*)(v3 + 0xCDC) = 1;
		}
		result = (*(int(__fastcall**)(__int64))(*(__int64*)v3 + 0x1728i64))(v3);
		if (result && id::functions::isPuppetMaster(v3)) {
			if (id::functions::isCanGKunai(v3) == 1) {
				partnerAddr = *(__int64*)(v3 + 0x1050);
				*(DWORD*)(partnerAddr + 0xCC8) = 67;
				*(DWORD*)(partnerAddr + 0xCDC) = 1;
			}
			return 0;
		}
	}
	else {
		result = (*(int(__fastcall**)(__int64))(*(__int64*)v3 + 0x1728i64))(v3);
		if (result && id::functions::isPuppetMaster(v3)) {
			if (id::functions::isCanGKunai(v3) == 1) {
				partnerAddr = *(__int64*)(v3 + 0x1050);
				*(DWORD*)(partnerAddr + 0xCC8) = 67;
				*(DWORD*)(partnerAddr + 0xCDC) = 1;
			}
			return 0;
		}
		globals::hookManager->getOriginal<decltype(&mechanics::functions::setMultiInputPlayerState)>(mechanics::functions::setMultiInputPlayerState)(a1, a2);
	}
}

//This function takes d-pad item inputs and sets the player state to nothing, item throw/use, and guardbreak pill.
//Modifications are for cancelling guard to item/guardbreak pill like in Storm Generations.
int mechanics::functions::itemState(__int64 a1, unsigned int a2) {

	if (!mechanics::enableGTI)
		return globals::hookManager->getOriginal<decltype(&mechanics::functions::itemState)>(mechanics::functions::itemState)(a1, a2);

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
	sub_140529598 osub_140529598 = (sub_140529598)(globals::moduleBase + 0x528998 + 0xC00);

	typedef __int64(__fastcall* sub_14074B034) (__int64 a1, __int64 a2, int a3);
	sub_14074B034 osub_14074B034 = (sub_14074B034)(globals::moduleBase + 0x74A434 + 0xC00);

	typedef int(__fastcall* sub_14079C5C0) (__int64 a1);
	sub_14079C5C0 osub_14079C5C0 = (sub_14079C5C0)(globals::moduleBase + 0x79B9C0 + 0xC00);

	typedef int(__fastcall* sub_1407ED2B4) (__int64 a1);
	sub_1407ED2B4 osub_1407ED2B4 = (sub_1407ED2B4)(globals::moduleBase + 0x7EC6B4 + 0xC00);

	typedef int(__fastcall* sub_1407E10D4) (__int64 a1);
	sub_1407E10D4 osub_1407E10D4 = (sub_1407E10D4)(globals::moduleBase + 0x7E04D4 + 0xC00);

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
	v9 = *(DWORD*)(playerAddr + 0x14B30);
	if ((((*(DWORD*)(playerAddr + 0x14B30) != 0 ? v8 : 0) || *(DWORD*)(playerAddr + 0xCC0) == 73)) && v4 != -1) //State Checking + If item slot is available
	{
		DWORD(v9) = (*(int(__fastcall**)(__int64, __int64))(*(__int64*)playerAddr + 0x1758i64))(
			playerAddr,
			(unsigned int)v4);
		if ((DWORD)v9)
		{
			v10 = globals::moduleBase + 0x14161C8C8 - 0x140000000 + 0xC00;
			v11 = osub_140529598((__int64)"BATTLE_ITEM150");// gb pill
			v12 = osub_140529598((__int64)"BATTLE_ITEM192");
			if (v4 != 0)         // if it's not a gb pill&& v12 == v15
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

//Function that runs every frame that affects all characters in a combo state. Modifications are for disabling shadow state with full combo switch.
signed __int64 mechanics::functions::areYouComboing(__int64 playerAddr, unsigned int playerState, unsigned int a3) {
	std::uintptr_t addrGameRate = (std::uintptr_t)(globals::moduleBase + 0x161A334);
	if (*(float*)(addrGameRate) == 0.4f && *(DWORD*)(playerAddr + 0xCC0) == 66) 
		*(DWORD*)(playerAddr + 0x14C60) = 0;
	return globals::hookManager->callOriginal<decltype(&mechanics::functions::areYouComboing)>(mechanics::functions::areYouComboing, playerAddr, playerState, a3);
}

//Function that runs when movement actions are chained together such as jump/nm to jump/nm. Modifications are for rev NM: NM and NMK to jump.
__int64 mechanics::functions::movementChain(void* rcx, int a1, __int64 a2, __int64 a3) {
	int v3; // ebp@1
	__int64 playerAddr; // rbx@1
	signed int v5; // esi@1
	int v6; // eax@3
	__int64 v7; // rcx@3
	__int64* v8; // rdx@6
	signed __int64 playerState; // rdx@23
	__int64 result; // rax@33

	typedef __int64(__fastcall* sub_1407C0DD8) (__int64 a1, int a2);
	sub_1407C0DD8 osub_1407C0DD8 = (sub_1407C0DD8)(globals::moduleBase + 0x7C01D8 + 0xC00);

	typedef __int64(__fastcall* sub_1407C0748) (__int64 a1, int a2);
	sub_1407C0748 osub_1407C0748 = (sub_1407C0748)(globals::moduleBase + 0x7BFB48 + 0xC00);

	typedef __int64(__fastcall* sub_140A046F0) (__int64 a1);
	sub_140A046F0 osub_140A046F0 = (sub_140A046F0)(globals::moduleBase + 0xA03AF0 + 0xC00);

	typedef __int64(__fastcall* sub_1407926B4) (__int64 a1, int a2);
	sub_1407926B4 osub_1407926B4 = (sub_1407926B4)(globals::moduleBase + 0x7C01D8 + 0xC00);

	typedef int(__fastcall* sub_140A04970) (__int64 a1);
	sub_140A04970 osub_140A04970 = (sub_140A04970)(globals::moduleBase + 0xA03D70 + 0xC00);

	typedef __int64(__fastcall* sub_1407AE694) (__int64 a1);
	sub_1407AE694 osub_1407AE694 = (sub_1407AE694)(globals::moduleBase + 0x7ADA94 + 0xC00);

	playerAddr = (__int64)rcx;
	__int64 baseInputAddr = playerAddr + 0x218;

	if ((*(DWORD*)(playerAddr + 0xCC0) == 10 || *(DWORD*)(playerAddr + 0xCC0) == 11 || *(DWORD*)(playerAddr + 0xCC0) == 12) && !mechanics::enableRevNM) {
		return globals::hookManager->getOriginal<decltype(&mechanics::functions::movementChain)>(mechanics::functions::movementChain)(rcx, a1, a2, a3);
	}
	if ((*(DWORD*)(playerAddr + 0xCC0) == 69) && !mechanics::enableRevNMK) {
		return globals::hookManager->getOriginal<decltype(&mechanics::functions::movementChain)>(mechanics::functions::movementChain)(rcx, a1, a2, a3);
	}
	if (*(DWORD*)(playerAddr + 0xCC0) == 4 || *(DWORD*)(playerAddr + 0xCC0) == 5 || *(DWORD*)(playerAddr + 0xCC0) == 8) {
		return globals::hookManager->getOriginal<decltype(&mechanics::functions::movementChain)>(mechanics::functions::movementChain)(rcx, a1, a2, a3);
	}
	float analogZone = *(float*)(playerAddr + 0x1B0 + 0x70);
	if (analogZone < 0.5f) {
		*(DWORD*)(playerAddr + 0xCC8) = 4;
		*(DWORD*)(playerAddr + 0xCDC) = 1;
		result = osub_1407AE694(playerAddr);
		return result;
	}
	else {
		return globals::hookManager->getOriginal<decltype(&mechanics::functions::movementChain)>(mechanics::functions::movementChain)(rcx, a1, a2, a3);
	}
	if ((a3 == 0 && (a2 == 0 || a2 == 1 || a2 == 2)) || ((a2 == 0 || a2 == 1) && a3 == 1)) {
	}
	else {
		return globals::hookManager->getOriginal<decltype(&mechanics::functions::movementChain)>(mechanics::functions::movementChain)(rcx, a1, a2, a3);
	}
	v3 = a1;
	v5 = 0;
	if (*(DWORD*)(playerAddr + 0xCC0) == 4 || *(DWORD*)(playerAddr + 0xCC0) == 5 || *(DWORD*)(playerAddr + 0xCC0) == 8 || *(DWORD*)(playerAddr + 0xCC0) == 69) {
		return globals::hookManager->getOriginal<decltype(&mechanics::functions::movementChain)>(mechanics::functions::movementChain)(rcx, a1, a2, a3);
	}
	if ((*(int (**)(void))(*(__int64*)playerAddr + 0xE78i64))() && (DWORD)(playerAddr + 0xCC0) != 9)
	{
		v6 = osub_1407C0DD8(playerAddr + 0x218, 0);
		v7 = playerAddr + 0x218;
		if (v6)
		{
			return globals::hookManager->getOriginal<decltype(&mechanics::functions::movementChain)>(mechanics::functions::movementChain)(rcx, a1, a2, a3);
		}
		else
		{
			osub_1407C0748(v7, 0);
			if (*(float*)&a3 <= 0.5)
			{
				osub_140A04970(playerAddr + 0x1417C);
				if (*(float*)&a3 < 1.0f) {
					if (*(float*)&a3 < 0.0f) {
						return globals::hookManager->getOriginal<decltype(&mechanics::functions::movementChain)>(mechanics::functions::movementChain)(rcx, a1, a2, a3);
					}
					if (*(DWORD*)(playerAddr + 0x14198) == 0) {
						v5 = osub_1407AE694(playerAddr);
						goto LABEL_33;
					}
				}
				else {
					return globals::hookManager->getOriginal<decltype(&mechanics::functions::movementChain)>(mechanics::functions::movementChain)(rcx, a1, a2, a3);
				}
			}
			return globals::hookManager->getOriginal<decltype(&mechanics::functions::movementChain)>(mechanics::functions::movementChain)(rcx, a1, a2, a3);
		}
	}
	else {
		return globals::hookManager->getOriginal<decltype(&mechanics::functions::movementChain)>(mechanics::functions::movementChain)(rcx, a1, a2, a3);
	}
LABEL_33:
	*(DWORD*)(playerAddr + 0xCC8) = 4;
	*(DWORD*)(playerAddr + 0xCDC) = 1;
	result = (unsigned int)v5;
	return result;
}

//Function that runs when players have a chakra dash state. Modifications are for Gens/S3 Instant ACD.
__int64 __fastcall mechanics::functions::cdashState(void* rcx, __int64 a1, int a2, float a3) {
	if (!mechanics::enableInstantACD)
		return globals::hookManager->callOriginal<decltype(&mechanics::functions::cdashState)>(mechanics::functions::cdashState, rcx, a1, a2, a3);
	__int64 playerAddr = (__int64)rcx;
	if (*(DWORD*)(playerAddr + 0xCCC) == 4) {
		*(DWORD*)(playerAddr + 0xCCC) = 6;
		return 6;
	}
	else {
		return globals::hookManager->callOriginal<decltype(&mechanics::functions::cdashState)>(mechanics::functions::cdashState, rcx, a1, a2, a3);
	}
}

//Function that runs when players are in a back chakra dash state, for the purposes of spark. Modifications include Generations Air Back Chakra Dash Spark.
int mechanics::functions::backACD(__int64 a1, int a2) {
	int retVal = globals::hookManager->getOriginal<decltype(&mechanics::functions::backACD)>(mechanics::functions::backACD)(a1, a2);
	if (((*(DWORD*)(a1 + 0xCC0) == 17) && (*(DWORD*)(a1 + 0xCC4) == 64) && (*(DWORD*)(a1 + 0xCCC) == 0)) && mechanics::enableABCDSpark)
		*(DWORD*)(a1 + 0xCCC) = 1;
	return retVal;
}

//Function that sets dash priority to numbers greater than 0. Modifications includes increased priority for back chakra dash and charged chakra dash.
void __fastcall mechanics::functions::setDashPriority(__int64 a1, int a2) {
	if (mechanics::enableDashPriority) {
		if (a2 == 349)
			a2 = 350;
		if (*(DWORD*)(a1 + 0x14A90) == 1)
			a2 = 351;
	}
	*(DWORD*)(a1 + 0x1403C) = a2;
	*(DWORD*)(a1 + 0x14044) = a2;
}

//Writes states for support characters. Modifications include chakra shuriken cover fire.
int __fastcall mechanics::functions::writeSupportState(__int64 a1, unsigned int a2) {
	if (mechanics::enableCFCS) {
		if (*(DWORD*)(a1 + 0xCC0) == 214) {
			if (a2 == 67)
				a2 = 70;
			if (a2 == 68)
				a2 = 71;
		}
	}
	return globals::hookManager->callOriginal<decltype(&mechanics::functions::writeSupportState)>(mechanics::functions::writeSupportState, a1, a2);
}

//Writes bytes relating to switch priorities(Whether instantly cancelled or not)
//Modifications include shuriken, chakra shuriken, tilt, and grab priority.
int __fastcall mechanics::functions::writeSwitchByte(__int64 a1) {
	int playerState = *(DWORD*)(a1 + 0xCC0);
	if ((playerState == 66 && mechanics::enableTiltSwitch) || (playerState == 67 && mechanics::enableShurikenSwitch) || (playerState == 70 && mechanics::enableChakraShurikenSwitch) || (playerState == 72 && mechanics::enableGrabSwitch)) {
		*(DWORD*)(a1 + 0x14C14) = 1;
		return playerState;
	}
	else
		return globals::hookManager->callOriginal<decltype(&mechanics::functions::writeSwitchByte)>(mechanics::functions::writeSwitchByte, a1);
}

//Runs when a guard break occurs from a combo. Modifications include a fix for Six Paths Madara limbo clones crash. 
int mechanics::functions::comboGuardBreak(__int64 a1, __int64 a2, __int64 a3, __int64 a4) {
	if (*(DWORD*)(a1 + 0xC14) == 1701736302) {
		if (*(DWORD*)(a1 + 0xC8C) == 0)
		return globals::hookManager->callOriginal<decltype(&mechanics::functions::comboGuardBreak)>(mechanics::functions::comboGuardBreak, mechanics::limboCloneAddr, a2, a3, a4);
		else
			return globals::hookManager->callOriginal<decltype(&mechanics::functions::comboGuardBreak)>(mechanics::functions::comboGuardBreak, a1, a2, a3, a4);
	}
	return globals::hookManager->callOriginal<decltype(&mechanics::functions::comboGuardBreak)>(mechanics::functions::comboGuardBreak, a1, a2, a3, a4);
}