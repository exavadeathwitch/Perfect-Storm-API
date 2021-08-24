#include <iostream>
#include <string>

#include "Stage.h"
#include "Memory.h"
#include "Functions.h"
#include "MinHook.h"
#include "SDL2/SDL2Music.h"
#include "Music.h"

void moddingApi::Stage::getStageName(__int64 a1) {
	std::string initialName = moddingApi::Memory::strFromAddrSmall(a1);
	if ((initialName == "LTAGE_") || (initialName == "STAGE_")) {
		stageName = moddingApi::Memory::strFromAddrMax(a1);
		std::cout << stageName << std::endl;
	}
}

typedef __int64(__fastcall* battleEnd)(__int64 a1, int a2, __int64 a3, __int64 a4);
battleEnd oBattleEnd = NULL;

__int64 __fastcall nBattleEnd(__int64 a1, int a2, __int64 a3, __int64 a4)
{
	std::cout << "end" << std::endl;
	SDL2Music music;
	music.Halt_Music();
	return oBattleEnd(a1, a2, a3, a4);
}

typedef int(__fastcall* battleBegin)(__int64 rcx, __int64 a1, float a2);
battleBegin oBattleBegin = NULL;

int __fastcall nBattleBegin(__int64 rcx, __int64 a1, float a2) {
	
	typedef __int64(__fastcall* sub_14074E240) (__int64 a1);
	sub_14074E240 osub_14074E240 = (sub_14074E240)(moddingApi::Memory::moduleBase + 0x74D640 + 0xC00);

	if (*(DWORD*)(rcx + 4 * osub_14074E240(moddingApi::Memory::GetQword(0x14161C8C8)) + 0x80) == 1) {
	std::cout << "begin" << std::endl;
	SDL2Music music;
	music.Halt_Music();
	moddingApi::Music::PlayStageMusicTrack();
}
	return oBattleBegin(rcx, a1, a2);
}

void moddingApi::Stage::stageHooks() {

		bool status;
		std::cout << "lets go" << std::endl;
		std::uintptr_t addrBattleEnd = (std::uintptr_t)(moddingApi::Memory::moduleBase + 0x70C478 + 0xC00);
		std::uintptr_t addrBattleBegin = (std::uintptr_t)(moddingApi::Memory::moduleBase + 0x74C648 + 0xC00);

		status = MH_CreateHook((LPVOID)addrBattleEnd, nBattleEnd, (LPVOID*)(&oBattleEnd));
		if (status != MH_OK)
		{
			std::cout << "could not create hook BattleEnd" << std::endl;
		}

		status = MH_EnableHook((LPVOID)addrBattleEnd);
		if (status != MH_OK)
		{
			std::cout << "could not enable hook BattleEnd" << std::endl;
		}
		
		status = MH_CreateHook((LPVOID)addrBattleBegin, nBattleBegin, (LPVOID*)(&oBattleBegin));
		if (status != MH_OK)
		{
			std::cout << "could not create hook BattleEnd" << std::endl;
		}

		status = MH_EnableHook((LPVOID)addrBattleBegin);
		if (status != MH_OK)
		{
			std::cout << "could not enable hook BattleEnd" << std::endl;
		}
	
}