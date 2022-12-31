#include "pch.hpp"

#include "nuccSys.hpp"

#include "Game/ccTaskManager/ccTaskManager.hpp"

#include "Game/Framework/Framework.hpp"

int nuccSys::Update(__int64 gameInfo) {
	__int64 v4 = 0x50i64;
	unsigned int v3 = 128;
	//v3 = -1;
	//v4 = 0x55i64;
	//globals::hookManager->callOriginal<decltype(&ccTaskManager::Execute)>(ccTaskManager::Execute, *(__int64*)(mainlooppointer + 80), v4, v3, 1);
	//ccTaskManager::Execute((__int64*)(mainlooppointer + 80), v4, v3, 1);// render
	auto retval = globals::hookManager->callOriginal<decltype(&nuccSys::Update)>(nuccSys::Update, gameInfo);
	return retval;
	//return globals::hookManager->callOriginal<decltype(&nuccSys::Update)>(nuccSys::Update, gameInfo);
}