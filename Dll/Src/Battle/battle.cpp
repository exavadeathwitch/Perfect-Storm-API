#include <iostream>

#include "pch.hpp"

#include "battle.hpp"

#include "Player/Mechanics/mech.hpp"

#include "Util/Sound/SDL2Music.h"

#include "Util/Sound/Music.hpp"

#include "Core/ModConsole/ModConsole.hpp"

#include "Net/Online Training/oTraining.hpp"

//This function increases the match count variable. Modifications include music playing at the start of the round, making shadow state work for full combo switch, and changing regions in memory for mechanics that are enabled through doing so.
int __fastcall Battle::functions::matchCount(__int64 rcx, __int64 a1, float a2) {
	typedef __int64(__fastcall* sub_14074E240) (__int64 a1);
	sub_14074E240 osub_14074E240 = (sub_14074E240)(globals::moduleBase + 0x74D640 + 0xC00);
	std::uintptr_t addrGameRate = (std::uintptr_t)(globals::moduleBase + 0x161A334);
	if (mechanics::enableFullComboSwitch) {
		if (!mechanics::fullComboSwitchBytes) {
			util::memory::Modify::write_bytes<7>(globals::moduleBase + 0x7C059A + 0xC00, { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 });
			util::memory::Modify::write_bytes<5>(globals::moduleBase + 0x5741AD + 0xC00, { 0x90, 0x90, 0x90, 0x90, 0x90 });
			util::memory::Modify::write_bytes<5>(globals::moduleBase + 0x575C3E + 0xC00, { 0x90, 0x90, 0x90, 0x90, 0x90 });
			util::memory::Modify::write_bytes<5>(globals::moduleBase + 0x573F90 + 0xC00, { 0x90, 0x90, 0x90, 0x90, 0x90 });
			mechanics::fullComboSwitchBytes = 1;
		}
	if (*(float*)(addrGameRate) == 1.0f) {
		mechanics::fullComboSwitchShadowState = 0;
	}
	}

	if (!mechanics::enableFullComboSwitch) {
		if (mechanics::fullComboSwitchBytes) {
			util::memory::Modify::write_bytes<7>(globals::moduleBase + 0x7C059A + 0xC00, { mechanics::FC1[0], mechanics::FC1[1], mechanics::FC1[2], mechanics::FC1[3], mechanics::FC1[4], mechanics::FC1[5], mechanics::FC1[6] });
			util::memory::Modify::write_bytes<5>(globals::moduleBase + 0x5741AD + 0xC00, { mechanics::FC2[0], mechanics::FC2[1], mechanics::FC2[2], mechanics::FC2[3], mechanics::FC2[4] });
			util::memory::Modify::write_bytes<5>(globals::moduleBase + 0x575C3E + 0xC00, { mechanics::FC3[0], mechanics::FC3[1], mechanics::FC3[2], mechanics::FC3[3], mechanics::FC3[4] });
			util::memory::Modify::write_bytes<5>(globals::moduleBase + 0x573F90 + 0xC00, { mechanics::FC4[0], mechanics::FC4[1], mechanics::FC4[2], mechanics::FC4[3], mechanics::FC4[4] });
			mechanics::fullComboSwitchBytes = 0;
		}
	}

	if (mechanics::enableTiltCancels) {
		if (!mechanics::tiltNMJumpBytes) {
			util::memory::Modify::write_bytes<4>(globals::moduleBase + 0x77E621 + 0xC00, { 0x90, 0x90, 0x90, 0x90});
			mechanics::tiltNMJumpBytes = 1;
		}
	}

	if (!mechanics::enableTiltCancels) {
		if (mechanics::tiltNMJumpBytes) {
			util::memory::Modify::write_bytes<4>(globals::moduleBase + 0x77E621 + 0xC00, { mechanics::TC1[0], mechanics::TC1[1], mechanics::TC1[2], mechanics::TC1[3]});
			mechanics::tiltNMJumpBytes = 0;
		}
	}
	Battle::inBattle = 1;
	Battle::matchCount = *(DWORD*)(rcx + 4 * osub_14074E240(globals::moduleBase + 0x14161C8C8 - 0x140000000 + 0xC00) + 0x80);
	//std::cout << "matchcount: " << Battle::matchCount << std::endl;
	//Battle Starts
	if (*(DWORD*)(rcx + 4 * osub_14074E240(globals::moduleBase + 0x14161C8C8 - 0x140000000 + 0xC00) + 0x80) == 1) {
		SDL2Music music;
		if (music.Playing_Music() != 0) {
			music.Halt_Music();
		}
		//util::memory::Modify::write_bytes<5>(globals::moduleBase + 0xA4357B + 0xC00, { 0x90, 0x90, 0x90, 0x90, 0x90 });
		Battle::inBattle = 1;
		console::enabled = 1;
		music::functions m;
		m.playStageMusicTrack();

		OTraining::selectedLItem = 0;
		OTraining::tcheckBox[0] = false;
		OTraining::tcheckBox[1] = false;
		OTraining::tcheckBox[2] = false;
		OTraining::tcheckBox[3] = false;
		OTraining::tcheckBox[4] = false;
		OTraining::selectedSGItem = 0;
	}
	return globals::hookManager->callOriginal<decltype(&Battle::functions::matchCount)>(Battle::functions::matchCount, rcx, a1, a2);
}

//This function is used for when the battle concludes. Modifications include stopping the BGM when this occurs.
__int64 __fastcall Battle::functions::battleEnd(__int64 a1, int a2, __int64 a3, __int64 a4) {
	SDL2Music music;
	music.Halt_Music();
	Battle::inBattle = 0;
	console::enabled = 0;
	OTraining::selectedLItem = 0;
	OTraining::tcheckBox[0] = false;
	OTraining::tcheckBox[1] = false;
	OTraining::tcheckBox[2] = false;
	OTraining::tcheckBox[3] = false;
	OTraining::tcheckBox[4] = false;
	OTraining::selectedSGItem = 0;
	return globals::hookManager->callOriginal<decltype(&Battle::functions::battleEnd)>(Battle::functions::battleEnd, a1, a2, a3, a4);
}

//This function is used for when the battle disconnects during an online match. Modifications include stopping the BGM when this occurs.
__int64 __fastcall Battle::functions::loadDisconnectPopUp(__int64 a1) {
	Battle::inBattle = 0;
	console::enabled = 0;
	OTraining::selectedLItem = 0;
	OTraining::tcheckBox[0] = false;
	OTraining::tcheckBox[1] = false;
	OTraining::tcheckBox[2] = false;
	OTraining::tcheckBox[3] = false;
	OTraining::tcheckBox[4] = false;
	OTraining::selectedSGItem = 0;

	return globals::hookManager->callOriginal<decltype(&Battle::functions::loadDisconnectPopUp)>(Battle::functions::loadDisconnectPopUp, a1);
}