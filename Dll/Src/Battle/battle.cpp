#include "pch.hpp"

#include "battle.hpp"

#include "Util/Sound/SDL2Music.h"
/*
//This function increases the match count variable. Modifications include music playing at the start of the round.
int __fastcall Battle::functions::matchCount(__int64 rcx, __int64 a1, float a2) {
	typedef __int64(__fastcall* sub_14074E240) (__int64 a1);
	sub_14074E240 osub_14074E240 = (sub_14074E240)(globals::moduleBase + 0x74D640 + 0xC00);

	if (*(DWORD*)(rcx + 4 * osub_14074E240(globals::moduleBase + 0x14161C8C8 - 0x140000000 + 0xC00) + 0x80) == 1) {
		SDL2Music music;
		music.Halt_Music();
		moddingApi::Music::PlayStageMusicTrack();
	}
	return globals::hookManager->callOriginal<decltype(&mechanics::functions::matchCount)>(mechanics::functions::matchCount, rcx, a1, a2);
}

//This function is used for when the battle concludes. Modifications include stopping the BGM when this occurs.
__int64 __fastcall Battle::functions::battleEnd(__int64 a1, int a2, __int64 a3, __int64 a4) {
	SDL2Music music;
	music.Halt_Music();
	return globals::hookManager->callOriginal<decltype(&mechanics::functions::battleEnd)>(mechanics::functions::battleEnd, a1, a2, a3, a4);
}
*/