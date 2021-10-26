#include "pch.hpp"

#include "General/general.hpp"

#include "Battle/battle.hpp"

#include "Stage/Stage.hpp"

#include "Util/Sound/SDL2Music.h"

#include "Core/Globals.hpp"

#include "Util/Sound/Music.hpp"

#include <iostream>

#include <filesystem>

#include <vector>

#include <stdio.h>

__int64 __fastcall General::functions::getMemString(__int64 a1, int a2) {
	Stage::functions::getStageName(a1);
	return globals::hookManager->callOriginal<decltype(&General::functions::getMemString)>(General::functions::getMemString, a1, a2);
}

//Ran when music track is selected to be played. Modifications include playing specific tracks based on whichever tracks are chosen. Ex: Main Menu, 
signed __int64 __fastcall General::functions::musicTrack(__int64 a1, __int64 a2, int a3) {
	//std::cout << a3 << std::endl;
	const auto retval = globals::hookManager->getOriginal<decltype(&General::functions::musicTrack)>(General::functions::musicTrack)(a1, a2, a3);
	music::functions m;
	m.playMenuMusicTrack(a3);

	return retval;
}

//Ran when music fades. Modifications include making the custom bgm fade when in-game music fades.
int __fastcall General::functions::noMusicTrack(__int64 a1, __int64 a2, __int64 a3) {
	const auto retval = globals::hookManager->getOriginal<decltype(&General::functions::noMusicTrack)>(General::functions::noMusicTrack)(a1, a2, a3);
	//std::cout << std::hex << (a1 + 4i64 * (signed int)a3 + 156) << std::dec << std::endl;
	if (*(DWORD*)(a1 + 4i64 * (signed int)a3 + 156) == -1) {
		SDL2Music music;
		if (music.Playing_Music() != 0)
		music.Fade_Out(1500);
	}
	return retval;
}

//Ran when music fades. Modifications include making the custom bgm fade when in-game music fades.
signed __int64 __fastcall General::functions::makeGameFocus(__int64 a1) {
	const auto retval = globals::hookManager->getOriginal<decltype(&General::functions::makeGameFocus)>(General::functions::makeGameFocus)(a1);
		SDL2Music music;

		if (music.Playing_Music() != 0)
		music.Play_Pause();
	return retval;
}

//Ran when music fades. Modifications include making the custom bgm fade when in-game music fades.
signed __int64 __fastcall General::functions::makeGameNotFocus(__int64 a1) {
	//const auto retval = globals::hookManager->getOriginal<decltype(&General::functions::makeGameNotFocus)>(General::functions::makeGameNotFocus)(a1);
		//SDL2Music music;
		
		//if (music.Playing_Music() != 0)
		//music.Play_Pause();
	return 1;
}

int General::functions::loadCpkInitial() {
	__int64 v0; // rax@1
	__int64 v1; // rbx@1
	unsigned int ActualVersion; // eax@3
	unsigned int GameVersion; // ebx@3
	__int64 v4; // rbx@5
	signed __int64 v5; // rdi@5
	const char* v6; // rax@10
	void* v7; // rdx@13
	void* v8; // rbx@16
	int v9; // eax@16
	//const char *v11; // [sp+20h] [bp-188h]@12
	//int v12; // [sp+28h] [bp-180h]@12
	void* Memory; // [sp+30h] [bp-178h]@5
	int v14; // [sp+38h] [bp-170h]@5
	const char* v15; // [sp+40h] [bp-168h]@5
	unsigned __int64 v16; // [sp+48h] [bp-160h]@5
	const char* v17; // [sp+50h] [bp-158h]@5
	int v18; // [sp+58h] [bp-150h]@5
	const char* v19; // [sp+60h] [bp-148h]@5
	int v20; // [sp+68h] [bp-140h]@5
	const char* v21; // [sp+70h] [bp-138h]@5
	int v22; // [sp+78h] [bp-130h]@5
	const char* v23; // [sp+80h] [bp-128h]@5
	int v24; // [sp+88h] [bp-120h]@5
	__int64* v25; // [sp+90h] [bp-118h]@4
	signed int v26; // [sp+98h] [bp-110h]@4
	__int64 v27; // [sp+A0h] [bp-108h]@4
	__int64 retaddr; // [sp+1A8h] [bp+0h]@1s
	//std::cout << "test" << std::endl;

	//Sleep(5000);
	//int region = *(int*)((__int64)(globals::moduleBase + 0x1416663C8 - 0x140000000) + 0x1D4);
	v0 = (__int64)&retaddr;
	const auto retval = globals::hookManager->getOriginal<decltype(&General::functions::loadCpkInitial)>(General::functions::loadCpkInitial)();


	// LOAD CUSTOM CPK
		cpkdata* c = (cpkdata*)malloc(sizeof(cpkdata));

		for (int x = 0; x < CpkToLoad.size(); x++)
		{
			typedef signed __int64(__fastcall* sub_14056C34C)(__int64 a);
			sub_14056C34C sub_14056C34C_f = (sub_14056C34C)(globals::moduleBase + 0x56B74C + 0xC00);

			GameVersion = CpkPriority.at(x);
			//std::cout << "Loaded cpk " << CpkToLoad.at(x) << std::endl;
			c->path = CpkToLoad.at(x);
			c->priority = 0;

			typedef signed __int64(__fastcall* sub_14056C3D4)(__int64 a, __int64 b);
			sub_14056C3D4 sub_14056C3D4_f = (sub_14056C3D4)(globals::moduleBase + 0x56B7D4 + 0xC00);
			sub_14056C3D4_f((__int64)c, GameVersion);
		}
	if ((__int64)(0x1415F8298 - 0x140000000))
	{
		//v11 = (const char *)1001;
		//v12 = 1003;

		// 0x56B284
		__int64 blab = *(__int64*)(globals::moduleBase + 0x1415F8298 - 0x140000000);
		typedef signed __int64(__fastcall* sub_14056BE84)(__int64 a);
		sub_14056BE84 sub_14056BE84_f = (sub_14056BE84)(globals::moduleBase + 0x56B284 + 0xC00);
		v0 = sub_14056BE84_f(blab);
		
	}

	return v0;
}

const char* General::functions::retTitleVer() {
	if (globals::settings->m_Version == "Enhanced")
		return " 1.09 Enhanced";
	else {
		return " 2.0";
	}
}