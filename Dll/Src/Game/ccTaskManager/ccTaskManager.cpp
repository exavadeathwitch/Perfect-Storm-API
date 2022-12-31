#include "pch.hpp"

#include "ccTaskManager.hpp"

#include "Core/SDK/Game.hpp"

#include "Core/DebugMenu/GameSpeed/GameSpeed.hpp"

#include "Util/Console/Console.hpp"

#include "Game/misc/misc.hpp"

#include "Game/Framework/Framework.hpp"

int cycle = 0;
__int64 ccTaskManager::Execute(__int64 a1, __int64 a2, unsigned int a3, int a4) {
	//util::console::debugPrint((std::to_string(a2) + "\n").c_str());
	/*
	if (a2 == 85) {
		if (additional != NULL && start) {
			runagain = 1;
			misc::nummNXRequestDrawOpaqueCallback((__int64)(globals::moduleBase + 0x9A9A94), additional);
		}
	}*/
	if (enableFrameStep && a2 == 2) {
		if (frameStep) {
			frameStep = false;
			for (int x = 0; x < frameStepCount; x++)
				globals::hookManager->callOriginal<decltype(&ccTaskManager::Execute)>(ccTaskManager::Execute, a1, a2, a3, a4);
			return 0x0;
		}
		else
			return 0x0;
	}
	if ((gameSpeed == 0 || gameSpeed >= 2) && a2 == 2) {
		if (gameSpeed >= 2) {
			for (int x = 0; x < gameSpeed; x++) {
				globals::hookManager->callOriginal<decltype(&ccTaskManager::Execute)>(ccTaskManager::Execute, a1, a2, a3, a4);
			}
			return 0x0;
		}
		else {
			if (alternate == 1) {
				alternate = 0;
				return globals::hookManager->callOriginal<decltype(&ccTaskManager::Execute)>(ccTaskManager::Execute, a1, a2, a3, a4);
			}
			else
				alternate = 1;
			return 0x0;
		}
	}
	//util::console::debugPrint((std::to_string(a2) + ("\n")).c_str());
	return globals::hookManager->callOriginal<decltype(&ccTaskManager::Execute)>(ccTaskManager::Execute, a1, a2, a3, a4);
}