#include "pch.hpp"

#include "ccGame.hpp"

__int64 __fastcall ccGame_GetPlayerLeader(unsigned int a1) {
	return globals::hookManager->callOriginal<decltype(&ccGame_GetPlayerLeader)>(ccGame_GetPlayerLeader, a1);
}