#include "pch.hpp"

#include "mech.hpp"

#include "Player/IDs/id.hpp"

#include "imgui/include/imgui_impl_dx11.h"

#include "GameSettings/gameSettings.hpp"

#include "Player/Properties/prop.hpp"

#include <iostream>

//Initializes game mechanics depending on the version of the game selected.
void mechanics::functions::initializeMechanics() {
	if (globals::settings->m_Version == "Enhanced") {
		mechanics::enableNMTilt = 0;
		mechanics::enableGKunaiAirCombo = 0;
		mechanics::enableNMGrab = 1;
		mechanics::enableGKunai = 0;
		mechanics::enableShurikenComboTilt = 1;
		mechanics::enableTiltCancels = 0;
		mechanics::enableFullComboSwitch = 0;
		mechanics::enableFastACD = 1;
		mechanics::enableABCDSpark = 1;
		mechanics::enableDashPriority = 1;
		mechanics::enableRevNM = 1;
		mechanics::enableRevNMK = 1;
		mechanics::enableCFCS = 1;
		mechanics::enableGTI = 1;
		mechanics::enableTiltSwitch = 1;
		mechanics::enableGrabSwitch = 1;
		mechanics::enableShurikenSwitch = 1;
		mechanics::enableChakraShurikenSwitch = 1;
	}
	else {
	mechanics::enableNMTilt = 1;
	mechanics::enableGKunaiAirCombo = 1;
	mechanics::enableNMGrab = 1;
	mechanics::enableGKunai = 1;
	mechanics::enableShurikenComboTilt = 1;
	mechanics::enableTiltCancels = 1;
	mechanics::enableFullComboSwitch = 1;
mechanics::enableFastACD = 1;
mechanics::enableABCDSpark = 1;
mechanics::enableDashPriority = 1;
mechanics::enableRevNM = 1;
mechanics::enableRevNMK = 1;
mechanics::enableCFCS = 1;
mechanics::enableGTI = 1;
mechanics::enableTiltSwitch = 1;
mechanics::enableGrabSwitch = 1;
mechanics::enableShurikenSwitch = 1;
mechanics::enableChakraShurikenSwitch = 1;
	}
}

__int64 __fastcall mechanics::functions::airSpark(__int64 a1, float a2) {


	typedef int(__fastcall* sub_14079B980) (__int64 a1);
	sub_14079B980 osub_14079B980 = (sub_14079B980)(globals::moduleBase + 0x79AD80 + 0xC00);

	typedef __int64(__fastcall* sub_14079C994) (__int64 a1, unsigned int a2, float a3);
	sub_14079C994 osub_14079C994 = (sub_14079C994)(globals::moduleBase + 0x79BD94 + 0xC00);
	std::cout << "wow" << std::endl;
	const auto retval = globals::hookManager->getOriginal<decltype(&mechanics::functions::airSpark)>(mechanics::functions::airSpark)(a1, a2);
	__int64 v2 = a1;
	DWORD(v6) = osub_14079B980(v2);
	if (v6) {
		std::cout << "entered" << std::endl;
		osub_14079C994(v2, 1u, a2);
	}
	return retval;
}
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
	signed typedef __int64(__fastcall* sub_14079B950) (__int64 a1);
	sub_14079B950 osub_14079B950 = (sub_14079B950)(globals::moduleBase + 0x79AD50);

	if (a2 == 211) {
		*(DWORD*)(a1 + 0xFE50) = 1;
		*(DWORD*)(a1 + 0xFE54) = 0;
		*(DWORD*)(a1 + 0xFE74) = 0;
		__int64 inputPointer = a1 + 0x218;
		*(DWORD*)(inputPointer + 0x404) = 0;
		*(DWORD*)(inputPointer + 0x408) = 0;
		*(DWORD*)(inputPointer + 0x40C) = 0;
	}	if (a2 == 73 && *(DWORD*)(a1 + 0xCC0) == 154 && *(DWORD*)(a1 + 0x140A8) < 50)
		return 0;

	*(float*)(a1 + 0x1090) = 1.0f;
	if (a2 == 214) {
		*(DWORD*)(a1 + 0xFE50) = 1;
		*(DWORD*)(a1 + 0xFE54) = 0;
		*(DWORD*)(a1 + 0xFE74) = 0;
		__int64 inputPointer = a1 + 0x218;
		*(DWORD*)(inputPointer + 0x404) = 0;
		*(DWORD*)(inputPointer + 0x408) = 0;
		*(DWORD*)(inputPointer + 0x40C) = 0;
	}
	if (a2 == 213 && *(DWORD*)(a1 + 0xCC0) == 211) {
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
		//*(float*)(a1 + 0x1090) = 1.0f;
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

		//mechanics::functions::subCharge(playerAddr);
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
		if ((v3 || v4) && (*(int(__fastcall**)(__int64))(*(__int64*)playerAddr + 0xEA8i64))(playerAddr))
		{
			v6 = *(__int64*)playerAddr;
			if (v5)
			{
				(*(void(__fastcall**)(__int64, signed __int64, __int64, __int64))(v6 + 0xDE0))(playerAddr, 64i64, 0i64, 0i64);
				*(DWORD*)(playerAddr + 0x14DD8) = 0;
			}
			else
			{
				(*(void(__fastcall**)(__int64, signed __int64, __int64, signed __int64))(v6 + 0xDE0))(
					playerAddr,
					64i64,
					0i64,
					1i64);
			}
		}
		if ((((*(int(__fastcall**)(__int64, signed __int64))(*(__int64*)playerAddr + 0x1398i64))(playerAddr, 1i64)
			&& (((osub_1407C0CE8(v2, 0i64) && v4)) || (unsigned int)osub_1407C0DD8(v2, 9)))
			&& ((*(int(__fastcall**)(__int64))(*(__int64*)playerAddr + 0xEC8i64))(playerAddr)))) {
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

signed __int64 __fastcall mechanics::functions::canAC1(__int64 a1) {
	/*
	typedef __int64(__fastcall* sub_14077DA68) (__int64 a1, int a2, __int64 a3);
	sub_14077DA68 osub_14077DA68 = (sub_14077DA68)(globals::moduleBase + 0x77CE68 + 0xC00);

	signed typedef __int64(__fastcall* sub_14076C79C) (__int64 a1);
	sub_14076C79C osub_14076C79C = (sub_14076C79C)(globals::moduleBase + 0x76BB9C + 0xC00);

	typedef __int64(__fastcall* sub_1405950E0) ();
	sub_1405950E0 osub_1405950E0 = (sub_1405950E0)(globals::moduleBase + 0x5944E0 + 0xC00);

	v1 = a1;
	if ((unsigned int)osub_14076C79C(8)
		|| !*(DWORD*)(v1 + 84784)
		|| !osub_14077DA68(v1, 236, 1i64)
		|| !(*(int(__fastcall**)(__int64, __int64))(*(__int64*)v1 + 5016i64))(v1, 0i64))
	{
		return 0i64;
	}
	int playerState = *(DWORD*)(a1 + 0xCC0);
	if (4 <= playerState <= 6)
		return 1;
	*/
	
	const auto retval = globals::hookManager->getOriginal<decltype(&mechanics::functions::canAC1)>(mechanics::functions::canAC1)(a1);
	if (id::functions::isInGKunai(a1) && mechanics::enableGKunaiAirCombo)
		return 1;
	else
		return retval;
}

signed __int64 __fastcall mechanics::functions::canTilt(__int64 a1) {

	typedef signed __int64(__fastcall* sub_14076C79C) (int a1);
	sub_14076C79C osub_14076C79C = (sub_14076C79C)(globals::moduleBase + 0x76BB9C + 0xC00);

	typedef int(__fastcall* sub_14079C384) (__int64 a1);
	sub_14079C384 osub_14079C384 = (sub_14079C384)(globals::moduleBase + 0x79B784 + 0xC00);

	if (!mechanics::enableNMTilt)
		return globals::hookManager->getOriginal<decltype(&mechanics::functions::canTilt)>(mechanics::functions::canTilt)(a1);

	if (!(*(int(__fastcall**)(__int64, signed __int64))(*(__int64*)a1 + 5016i64))(a1, 1i64)
		|| (unsigned int)osub_14076C79C(8)
		|| (*(int(__fastcall**)(__int64))(*(__int64*)a1 + 4536i64))(a1) && osub_14079C384(a1) && !*(DWORD*)(a1 + 82412)
		|| !*(DWORD*)(a1 + 0x14B30))
	{
		return 0i64;
	}
	int playerState = *(DWORD*)(a1 + 0xCC0);
	if (10 <= playerState <= 12)
		return 1;
	else
		return globals::hookManager->getOriginal<decltype(&mechanics::functions::canTilt)>(mechanics::functions::canTilt)(a1);

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
	if ((((*(DWORD*)(v3 + 0xCC0) == 10) || (*(DWORD*)(v3 + 0xCC0) == 11) || (*(DWORD*)(v3 + 0xCC0) == 12)) && mechanics::functions::canGrab(a1)) && (osub_1407C0FAC(v2) || (unsigned int)osub_1407C0DD8(v2, 12))) {
		//|| ((*(DWORD*)(v3 + 0xCC0) == 10) || (*(DWORD*)(v3 + 0xCC0) == 11) || (*(DWORD*)(v3 + 0xCC0) == 12))
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
				if (!mechanics::enableGKunai)
					return globals::hookManager->getOriginal<decltype(&mechanics::functions::setMultiInputPlayerState)>(mechanics::functions::setMultiInputPlayerState)(a1, a2);
				partnerAddr = *(__int64*)(v3 + 0x1050);
				*(DWORD*)(partnerAddr + 0xCC8) = 67;
				*(DWORD*)(partnerAddr + 0xCDC) = 1;
			}
			return 0;
		}
	}
	else {
		result = (*(int(__fastcall**)(__int64))(*(__int64*)v3 + 0x1728i64))(v3);
		//mechanics::functions::pushBlock(v3);
		if (result && id::functions::isPuppetMaster(v3)) {
			if (id::functions::isCanGKunai(v3) == 1) {
				if (!mechanics::enableGKunai)
					return globals::hookManager->getOriginal<decltype(&mechanics::functions::setMultiInputPlayerState)>(mechanics::functions::setMultiInputPlayerState)(a1, a2);
				partnerAddr = *(__int64*)(v3 + 0x1050);
				*(DWORD*)(partnerAddr + 0xCC8) = 67;
				*(DWORD*)(partnerAddr + 0xCDC) = 1;
			}
			return 0;
		}
		return globals::hookManager->getOriginal<decltype(&mechanics::functions::setMultiInputPlayerState)>(mechanics::functions::setMultiInputPlayerState)(a1, a2);
	}
}

__int64 __fastcall mechanics::functions::canGrab(__int64 a1) {
	__int64 v1; // rbx@1
	int v3; // eax@5

	if (id::functions::isPartnerCharacter(a1))
		return globals::hookManager->getOriginal<decltype(&mechanics::functions::canGrab)>(mechanics::functions::canGrab)(a1);
	if (!mechanics::enableNMGrab)
		return globals::hookManager->getOriginal<decltype(&mechanics::functions::canGrab)>(mechanics::functions::canGrab)(a1);
	typedef __int64(__fastcall* sub_14077DA68) (__int64 a1, int a2, __int64 a3);
	sub_14077DA68 osub_14077DA68 = (sub_14077DA68)(globals::moduleBase + 0x77CE68 + 0xC00);

	signed typedef __int64(__fastcall* sub_14076C79C) (__int64 a1);
	sub_14076C79C osub_14076C79C = (sub_14076C79C)(globals::moduleBase + 0x76BB9C + 0xC00);

	typedef __int64(__fastcall* sub_1405950E0) ();
	sub_1405950E0 osub_1405950E0 = (sub_1405950E0)(globals::moduleBase + 0x5944E0 + 0xC00);

	v1 = a1;
	if (!*(DWORD*)(a1 + 84784) || *(DWORD*)(a1 + 85192) && osub_1405950E0())
		return 0i64;
	//std::cout << "past first if" << std::endl;
	v3 = *(DWORD*)(v1 + 0xC8C);
	if (v3 != 41 && v3 != 102 && v3 != 230 && !osub_14077DA68(v1, 248, 1i64) && !osub_14077DA68(v1, 247, 1i64))
		return 0i64;
	//std::cout << "past second if" << std::endl;
	if (!(*(int(__fastcall**)(__int64, signed __int64))(*(__int64*)v1 + 5016i64))(v1, 8i64))
		return 0i64;
	//std::cout << "past third if" << std::endl;
	if ((unsigned int)osub_14076C79C(8))
		return 0i64;
	//std::cout << "past fourth if" << std::endl;
	if ((unsigned int)(*(DWORD*)(v1 + 3272) - 74) <= 2)
		return 0i64;
	//std::cout << "past fifth if" << std::endl;
	int playerState = *(DWORD*)(a1 + 0xCC0);
	//std::cout << "past sixth if" << std::endl;
	if (playerState == 8)
		return 0;
	//std::cout << "past seventh if" << std::endl;
	if (playerState == 4 || playerState == 5 || playerState == 6)
		return 0;
	if (10 <= playerState <= 12)
		return 1;
	return globals::hookManager->getOriginal<decltype(&mechanics::functions::canGrab)>(mechanics::functions::canGrab)(a1);
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
			std::cout << v10 << std::endl;
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
	/*
	*(double*)(playerAddr + 0xB40) = 0;
	*(DWORD*)(playerAddr + 0x840) = 6;
	*/
	
	__int64 a1 = playerAddr;
	if (*(DWORD*)(a1 + 0xC8C) == 1234) {
		std::cout << "guard\n";
		*(DWORD*)(a1 + 0xC8C) = 0x46;
		//std::cout << *(DWORD*)(a1 + 0xC94) << std::endl;
		//__int64 addrsubtrahend = 0x7AFE56 + globals::moduleBase;
		/*
		std::vector<uint8_t> arrayOfByte(4);
		for (int i = 0; i < 4; i++)
			arrayOfByte[3 - i] = ((__int64)name - addrsubtrahend >> (i * 8));

		std::cout << std::hex << globals::moduleBase + 0x7AFE56 << std::endl;
		std::cout << std::hex << (__int64)name << std::endl;

		util::memory::Modify::write_bytes<4>(globals::moduleBase + 0x7AF252 + 0xC00, { arrayOfByte[3], arrayOfByte[2], arrayOfByte[1], arrayOfByte[0] });
		*/
		std::string bodname = "2itc00t0 trall";
		/*
		std::string sname = "2itceff1_grds"; //Start
		std::string lname = "2itceff1_grdl"; //Guard Anim
		std::string ename = "2itceff1_grde"; //Exit
		std::string effname = "2itceff1.xfbin";*/
		std::string sname = "2itceff1_awa_core00"; //Start
		std::string lname = "2itceff1_awa_core00"; //Guard Anim
		std::string ename = "2itceff1_awa_core00"; //Exit
		std::string effname = "2itceff1.xfbin";

		const std::array<unsigned char, 0x10> ogeffbytes = util::memory::Modify::read_bytes<0x10>(globals::moduleBase + 0xC00 + 0x10AB7F8 + 0x400);
		for (int i = 0; i < 10; i++) {
			if (i >= effname.length())
				util::memory::Modify::write_bytes<1>(globals::moduleBase + 0xC00 + 0x10AB7F8 + 0x400 + i, { 0x0 });
			else
				util::memory::Modify::write_bytes<1>(globals::moduleBase + 0xC00 + 0x10AB7F8 + 0x400 + i, { uint8_t(effname[i]) });
		}
		const std::array<unsigned char, 0x10> ogbodbytes = util::memory::Modify::read_bytes<0x10>(globals::moduleBase + 0xC00 + 0xF08810 + 0x400);
		for (int i = 0; i < 10; i++) {
			if (i >= bodname.length())
				util::memory::Modify::write_bytes<1>(globals::moduleBase + 0xC00 + 0xF08810 + 0x400 + i, { 0x0 });
			else
				util::memory::Modify::write_bytes<1>(globals::moduleBase + 0xC00 + 0xF08810 + 0x400 + i, { uint8_t(bodname[i]) });
		}
		const std::array<unsigned char, 0x24> ogsbytes = util::memory::Modify::read_bytes<0x24>(globals::moduleBase + 0xC00 + 0x10AB4F8 + 0x400);
		for (int i = 0; i < 24; i++) {
			if (i >= sname.length())
				util::memory::Modify::write_bytes<1>(globals::moduleBase + 0xC00 + 0x10AB4F8 + 0x400 + i, { 0x0 });
			else
				util::memory::Modify::write_bytes<1>(globals::moduleBase + 0xC00 + 0x10AB4F8 + 0x400 + i, { uint8_t(sname[i]) });
		}

		const std::array<unsigned char, 0x24> oglbytes = util::memory::Modify::read_bytes<0x24>(globals::moduleBase + 0xC00 + 0x10AB5B8 + 0x400);
		for (int i = 0; i < 24; i++) {
			if (i >= lname.length())
				util::memory::Modify::write_bytes<1>(globals::moduleBase + 0xC00 + 0x10AB5B8 + 0x400 + i, { 0x0 });
			else
				util::memory::Modify::write_bytes<1>(globals::moduleBase + 0xC00 + 0x10AB5B8 + 0x400 + i, { uint8_t(lname[i]) });
		}
		const std::array<unsigned char, 0x24> ogebytes = util::memory::Modify::read_bytes<0x24>(globals::moduleBase + 0xC00 + 0x10AB678 + 0x400);
		for (int i = 0; i < 24; i++) {
			if (i >= ename.length())
				util::memory::Modify::write_bytes<1>(globals::moduleBase + 0xC00 + 0x10AB678 + 0x400 + i, { 0x0 });
			else
				util::memory::Modify::write_bytes<1>(globals::moduleBase + 0xC00 + 0x10AB678 + 0x400 + i, { uint8_t(ename[i]) });
		}

		globals::hookManager->callOriginal<decltype(&prop::functions::CtrlGuardEffect)>(prop::functions::CtrlGuardEffect, a1, 1);

		*(DWORD*)(a1 + 0xC8C) = 0x19;
		for (int i = 0; i < 10; i++) {
			if (i >= ogeffbytes.size())
				util::memory::Modify::write_bytes<1>(globals::moduleBase + 0xC00 + 0x10AB7F8 + 0x400 + i, { 0x0 });
			else
				util::memory::Modify::write_bytes<1>(globals::moduleBase + 0xC00 + 0x10AB7F8 + 0x400 + i, { ogeffbytes[i] });
		}
		for (int i = 0; i < 10; i++) {
			if (i >= ogbodbytes.size())
				util::memory::Modify::write_bytes<1>(globals::moduleBase + 0xC00 + 0xF08810 + 0x400 + i, { 0x0 });
			else
				util::memory::Modify::write_bytes<1>(globals::moduleBase + 0xC00 + 0xF08810 + 0x400 + i, { ogbodbytes[i] });
		}

		for (int i = 0; i < 24; i++) {
			if (i >= ogsbytes.size())
				util::memory::Modify::write_bytes<1>(globals::moduleBase + 0xC00 + 0x10AB4F8 + 0x400 + i, { 0x0 });
			else
				util::memory::Modify::write_bytes<1>(globals::moduleBase + 0xC00 + 0x10AB4F8 + 0x400 + i, { ogsbytes[i] });
		}

		for (int i = 0; i < 24; i++) {
			if (i >= oglbytes.size())
				util::memory::Modify::write_bytes<1>(globals::moduleBase + 0xC00 + 0x10AB5B8 + 0x400 + i, { 0x0 });
			else
				util::memory::Modify::write_bytes<1>(globals::moduleBase + 0xC00 + 0x10AB5B8 + 0x400 + i, { oglbytes[i] });
		}

		for (int i = 0; i < 24; i++) {
			if (i >= ogebytes.size())
				util::memory::Modify::write_bytes<1>(globals::moduleBase + 0xC00 + 0x10AB678 + 0x400 + i, { 0x0 });
			else
				util::memory::Modify::write_bytes<1>(globals::moduleBase + 0xC00 + 0x10AB678 + 0x400 + i, { ogebytes[i] });
		}
	}
	std::uintptr_t addrGameRate = (std::uintptr_t)(globals::moduleBase + 0x161A334);
	if (mechanics::fullComboSwitchShadowState && *(DWORD*)(playerAddr + 0xCC0) == 63) {
		*(DWORD*)(playerAddr + 0x14C60) = 0;
		//std::cout << "fuck the shadow" << std::endl;
	}
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

//Runs when a blue dash hits the opponent. Modifications include a tracker for removing shadow state for full combo switch.
signed int __fastcall mechanics::functions::changeGameRateFromBlueDashHit(__int64 a1) {
	int retval = globals::hookManager->callOriginal<decltype(&mechanics::functions::changeGameRateFromBlueDashHit)>(mechanics::functions::changeGameRateFromBlueDashHit, a1);
	std::uintptr_t addrGameRate = (std::uintptr_t)(globals::moduleBase + 0x161A334);
	if (mechanics::enableFullComboSwitch) {
		if (*(float*)(addrGameRate) == 0.4f) {
			//std::cout << ".4f" << std::endl;
			mechanics::fullComboSwitchShadowState = 1;
		}
	}
	return retval;

}

//Runs the sub charge function.
void mechanics::functions::subCharge(__int64 baseAddr) {
	if (id::functions::isPartnerCharacter(baseAddr))
		return;
	__int64 buttonAddr = baseAddr + 0x218;
	__int64 healthAddr = id::functions::getHealthAddr(baseAddr);
	float subGauge = *(float*)(healthAddr + 0x20);
	if (*(DWORD*)(baseAddr + 0xCC0) == 1) {
		if (*(uint8_t*)(buttonAddr + 0x409) == *(uint8_t*)(buttonAddr + 0x599)) {
			if (subGauge < 100.0) {
				*(float*)(healthAddr + 0x20) = subGauge + .5f;
				*(float*)(baseAddr + 0x14B08) = 0;
			}
		}
	}
}

//Runs the pushblock function.
void mechanics::functions::pushBlock(__int64 baseAddr) {
	if (*(DWORD*)(baseAddr + 0xCC0) != 74)
		return;
	typedef __int64(__fastcall* sub_1407C09B8) (__int64 a1);
	sub_1407C09B8 osub_1407C09B8 = (sub_1407C09B8)(globals::moduleBase + 0x7BFDB8 + 0xC00);

	typedef signed __int64(__fastcall* sub_14076C770) ();
	sub_14076C770 osub_14076C770 = (sub_14076C770)(globals::moduleBase + 0x77CE68 + 0xC00);

	typedef __int64(__fastcall* sub_1407C0DD8) (__int64 a1, int a2);
	sub_1407C0DD8 osub_1407C0DD8 = (sub_1407C0DD8)(globals::moduleBase + 0x7C01D8 + 0xC00);
	if (id::functions::isPuppetMaster(baseAddr))
		return;
	if (id::functions::isPartnerCharacter(baseAddr))
		return;
	__int64 healthAddr = id::functions::getHealthAddr(baseAddr);
	float subGauge = *(float*)(healthAddr + 0x20);
	int stuff = *(DWORD*)(baseAddr + 0x14B30) != 0 ? 1 : 0;
	int v4 = (*(int(__fastcall**)(__int64, signed __int64))(*(__int64*)baseAddr + 5016i64))(baseAddr, 23i64) != 0 ? stuff : 0;
	int blab = *(DWORD*)(baseAddr + 0x141EC) != 0 ? v4 : 0;
	if (!(unsigned int)osub_1407C09B8(baseAddr + 0x218) && !(unsigned int)osub_1407C0DD8(baseAddr + 0x218, 36) || (unsigned int)osub_14076C770())
		blab = 0;
	if (blab == 1) {
		if (*(DWORD*)(baseAddr + 0xCC0) == 74 && subGauge >= 12.5f) {
			*(float*)(healthAddr + 0x20) = *(float*)(healthAddr + 0x20) - 12.5f;
			*(DWORD*)(baseAddr + 0xCC8) = 154;
			*(DWORD*)(baseAddr + 0xCDC) = 1;
		}
	}
}

int __fastcall mechanics::functions::counterState(__int64 a1, int a2) {
	const auto retval = globals::hookManager->callOriginal<decltype(&mechanics::functions::counterState)>(mechanics::functions::counterState, a1, a2);
	if (*(DWORD*)(a1 + 0xCC4) == 74) {
		*(uint8_t*)(a1 + 0x140A0) = 1;
		*(float*)(a1 + 0x140B0) = 5;
		if (*(DWORD*)(a1 + 0x141A8) <= 10) {
			*(DWORD*)(a1 + 0xCD0) = 0;
			*(DWORD*)(a1 + 0xCD4) = 0;
			*(DWORD*)(a1 + 0xFE60) = 0;
			*(DWORD*)(a1 + 0xFE64) = 0;
			*(float*)(a1 + 0x14B08) = 0;
			*(float*)(a1 + 0x1090) = .5f;
		}
	}
	return retval;
}

/*
int __fastcall mechanics::functions::counterState(__int64 a1, int a2)
{

	//return globals::hookManager->callOriginal<decltype(&mechanics::functions::counterState)>(mechanics::functions::counterState, a1, a2);
	DWORD v2; // rax@1
	__int64 v3; // rdi@1
	int v4; // edx@2
	__int64 v5; // rax@8
	__int64 v6; // r8@10
	__int64 v7; // rdx@15
	__int64* v8; // rax@17
	__int64 v9; // rcx@17
	__int64 v10; // xmm1@21
	__int64 v11; // rax@21
	__int64 v12; // xmm1@21
	__int64 v13; // xmm1@21
	__int64 v15; // [sp+20h] [bp-98h]@10
	__int64 v16; // [sp+40h] [bp-78h]@17
	__int64 v17; // [sp+50h] [bp-68h]@21
	__int64 v18; // [sp+60h] [bp-58h]@21
	__int64 v19; // [sp+70h] [bp-48h]@21
	std::string v20; // [sp+80h] [bp-38h]@17
	__int16 v21; // [sp+82h] [bp-36h]@17
	__int16 v22; // [sp+86h] [bp-32h]@17
	signed int v23; // [sp+88h] [bp-30h]@17
	int v24; // [sp+8Ch] [bp-2Ch]@17
	signed int v25; // [sp+90h] [bp-28h]@17
	signed int v26; // [sp+94h] [bp-24h]@17
	signed int v27; // [sp+98h] [bp-20h]@17
	__int16 v28; // [sp+9Ch] [bp-1Ch]@17
	void* retaddr; // [sp+B8h] [bp+0h]@1

	typedef void(__fastcall* blab) (__int64 a1);
	blab setPriorityto0 = (blab)(globals::moduleBase + 0x79BCFC + 0xC00);

	typedef int(__fastcall* sub_1407AE974) (__int64 a1);
	sub_1407AE974 osub_1407AE974 = (sub_1407AE974)(globals::moduleBase + 0x7ADD74 + 0xC00);

	typedef int(__fastcall* sub_140593DAC) (__int64 a1, unsigned int a2);
	sub_140593DAC osub_140593DAC = (sub_140593DAC)(globals::moduleBase + 0x5931AC + 0xC00);

	typedef int(__fastcall* sub_140763B9C) (__int64 a1, int a2, __int64 a3);
	sub_140763B9C osub_140763B9C = (sub_140763B9C)(globals::moduleBase + 0x7624E4 + 0xC00);

	typedef signed __int64(__fastcall* sub_14077E64C) (__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5, unsigned int a6);
	sub_14077E64C osub_14077E64C = (sub_14077E64C)(globals::moduleBase + 0x77DA4C + 0xC00);

	typedef __int64(__fastcall* sub_140A04DD0) ();
	sub_140A04DD0 osub_140A04DD0 = (sub_140A04DD0)(globals::moduleBase + 0xA041D0 + 0xC00);

	typedef __int64(__fastcall* sub_140AC0C30) (__int64 a1, int a2, __int64 a3, __int64 a4, int a5);
	sub_140AC0C30 osub_140AC0C30 = (sub_140AC0C30)(globals::moduleBase + 0xAC0030 + 0xC00);

	typedef int(__fastcall* sub_14076CDD4) (__int64 a1, int a2, unsigned int a3);
	sub_14076CDD4 osub_14076CDD4 = (sub_14076CDD4)(globals::moduleBase + 0x76C1D4 + 0xC00);

	typedef signed __int64(__fastcall* sub_140529BEC) (__int64 a1);
	sub_140529BEC osub_140529BEC = (sub_140529BEC)(globals::moduleBase + 0x528FEC + 0xC00);

	typedef void(__fastcall* blabby) (__int64 a1, int a2);
	blabby setPriorityToNot0 = (blabby)(globals::moduleBase + 0x79BD44 + 0xC00);

	typedef int(__fastcall* sub_14079BE5C) (__int64 a1, int a2);
	sub_14079BE5C osub_14079BE5C = (sub_14079BE5C)(globals::moduleBase + 0x79B25C + 0xC00);

	v3 = a1;
	std::cout << "pre first if" << std::endl;
	if (a2)
	{
		v2 = globals::hookManager->callOriginal<decltype(&mechanics::functions::counterState)>(mechanics::functions::counterState, a1, a2);
	}
	else
	{
		std::cout << "in else" << std::endl;
		osub_140593DAC(a1, 0x2Bu);
		std::cout << "after 1st" << std::endl;
		v5 = (*(int(__fastcall**)(__int64))(*(__int64*)v3 + 3464i64))(v3);
		std::cout << "after 2nd" << std::endl;
		//if (v5)
			//*(DWORD*)(v5 + 63856) = 1;
		//osub_140763B9C(v3, 176i64, (__int64)"pelvis");
		std::cout << "second if" << std::endl;
		if (!(*(int(__fastcall**)(__int64))(*(__int64*)v3 + 4576i64))(v3)
			|| *(DWORD*)(v3 + 0xC8C) == 25
			|| *(DWORD*)(v3 + 0xC8C) == 56
			|| *(DWORD*)(v3 + 0xC8C) == 85
			|| *(DWORD*)(v3 + 0xC8C) == 96
			|| (v7 = 87i64, *(DWORD*)(v3 + 0xC8C) == 193))
		{
			v7 = 71i64;
		}
		DWORD(v15) = 0;
		osub_14077E64C(v3, v7, 0, 0xFFFFFFFFi64, v15, 0);
		osub_140AC0C30(v3 + 62448, 0, v3 + 112, (__int64)osub_140A04DD0(), 1138819072);
		(*(void(__fastcall**)(signed __int64, __int64))(*(__int64*)(v3 + 62448) + 8i64))(v3 + 62448, 0i64);
		osub_14076CDD4(v3 + 82208, 1, 3u);
		sprintf((char*)&v16, "none");
		v9 = *(__int64*)(v3 + 85936);
		v24 = 0;
		v20 = -1;
		v21 = 0;
		v22 = 0;
		v23 = 1065353216;
		v25 = 1065353216;
		v26 = 1065353216;
		v27 = 1;
		v28 = 0;
		std::cout << "pre-third" << std::endl;
		//if ((*(int (**)(void))(*(__int64*)v9 + 40i64))())
			//v20 = "DAMAGE_ID_ATEMIHIT_SMASH";
		//if ((*(int (**)(void))(**(__int64**)(v3 + 0x14FB8) + 40i64))())
		//v20 = "DAMAGE_ID_ATEMIHIT_STAGGER";
		//v10 = v17;
		std::cout << "post-third" << std::endl;
		v23 = 0;
		v11 = *(__int64*)v3;
		v26 = 1065353216;
		v25 = 1065353216;
		*(float*)(v3 + 82016) = *(float*)&v16;
		*(float*)(v3 + 82032) = 0;
		//v12 = v19;
		v28 = 0;
		*(float*)(v3 + 0x14080) = 0;
		*(DWORD*)(v3 + 0x14090) = 1232;
		v13 = *(float*)&v25;
		*(std::string*)(v3 + 0x140A0) = 62;
		*(float*)(v3 + 0x140B0) = 1.0f;
		(*(void(__fastcall**)(__int64, signed __int64))(v11 + 4000))(v3, 16389i64);
		setPriorityToNot0(v3, 600);
		DWORD(v2) = osub_14079BE5C(v3, 31);
	}
	return (unsigned __int64)v2;
}
*/