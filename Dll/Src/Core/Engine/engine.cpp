#include "pch.hpp"

#include "engine.hpp"
inline bool speedo = 0;
int __fastcall engine::Engine::gamelogic(DWORD* a1) {
	return globals::hookManager->callOriginal<decltype(&engine::Engine::gamelogic)>(engine::Engine::gamelogic, a1);
};

__int64 __fastcall engine::Engine::pauseState(__int64 a1) {
	if (engine::runEngine)
		return globals::hookManager->callOriginal<decltype(&engine::Engine::pauseState)>(engine::Engine::pauseState, a1);
	return 0;
};