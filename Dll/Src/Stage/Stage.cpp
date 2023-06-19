#include "pch.hpp"

#include "Stage.hpp"

#include "Util/Memory/String.hpp"

#include "Util/Util.hpp"

#include "Camera/Camera.hpp"

#include <iostream>

void Stage::functions::getStageName(__int64 a1) {
	std::string initialName = util::memory::String::strFromAddrSpec(a1);
	//if (util::endsWith(util::memory::String::strFromAddr(a1), ".xfbin")) {
		//std::cout << util::memory::String::strFromAddr(a1) << std::endl;
	//}
	if (initialName == "STAGE") {
		stageName = util::memory::String::strFromAddr(a1);
		Camera::lockTitle = 0;
		//std::cout << Camera::lockTitle << std::endl;
		//std::cout << stageName << std::endl;
	}
	if (initialName == "S_STA") {
		fbStageName = util::memory::String::strFromAddr(a1);
	}
}

__int64 Stage::functions::stageselect(__int64 a1, __int64 a2) {
	//*(__int64*)(a2 + 0x30) = 1; 1 is select stage, 2 is back to menu
	auto retval = globals::hookManager->callOriginal<decltype(&Stage::functions::stageselect)>(Stage::functions::stageselect, a1, a2);
	*(DWORD*)(a1 + 0x18) = 0;
	return retval;
}