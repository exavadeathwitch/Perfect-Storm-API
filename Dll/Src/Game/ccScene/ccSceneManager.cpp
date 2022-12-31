#include "pch.hpp"

#include "ccSceneManager.hpp"

#include "Core/DebugMenu/DebugTitle/DebugTitle.hpp"
__int64 __fastcall ccSceneManager::Push(unsigned __int8* a1, int a2) {
	std::cout << a2 << std::endl;
	pushedscene = a2;
	if (bootFB && a2 == 4)
		return globals::hookManager->callOriginal<decltype(&ccSceneManager::Push)>(ccSceneManager::Push, a1, 3);
	if (skipOpening && a2 == 4)
		return globals::hookManager->callOriginal<decltype(&ccSceneManager::Push)>(ccSceneManager::Push, a1, 0x63);
	return globals::hookManager->callOriginal<decltype(&ccSceneManager::Push)>(ccSceneManager::Push, a1, a2);
}

__int64 __fastcall ccSceneManager::Execute(__int64 a1) {
	if (pushedscene == 9 && runTitle)
		return 0x0;
	return globals::hookManager->callOriginal<decltype(&ccSceneManager::Execute)>(ccSceneManager::Execute, a1);
}