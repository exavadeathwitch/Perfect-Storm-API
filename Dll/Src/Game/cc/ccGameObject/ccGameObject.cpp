#include "pch.hpp"

#include "ccGameObject.hpp"

#include "Core/SDK/Game.hpp"

#include "Core/DebugMenu/GameSpeed/GameSpeed.hpp"

#include "Util/Console/Console.hpp"


int ccGameObject::Update(__int64 a1) {
	__int64 pointer1 = *(__int64*)(a1 + 0x10);
	//__int64 pointer2 = *(__int64*)(pointer1);
	//util::console::debugPrint(("a1: " + std::to_string(a1) + "\n").c_str());
	//util::console::debugPrint(("beginscreen: " + std::format("{:x}", globals::moduleBase + 0x858CE8 + 0xC00) + "\n").c_str());
	//util::console::debugPrint(("pointer1: " + std::to_string(pointer1) + "\n").c_str());
	int pass = 0;
	for (int i = 0; i < sizeof(ccGameObjectarr); i++) {
		if (pointer1 == (__int64)(globals::moduleBase + ccGameObjectarr[i] + 0xC00) && ccGameObjectarr2[i] == false)
			pass = 1;
	}
	if (pass == 0)
		return globals::hookManager->callOriginal<decltype(&ccGameObject::Update)>(ccGameObject::Update, a1);
}