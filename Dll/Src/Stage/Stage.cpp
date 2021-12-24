#include "pch.hpp"

#include "Stage.hpp"

#include "Util/Memory/String.hpp"

#include "Util/Util.hpp"

#include "Camera/Camera.hpp"

#include <iostream>

void Stage::functions::getStageName(__int64 a1) {
	std::string initialName = util::memory::String::strFromAddrSpec(a1);
	//if (util::endsWith(util::memory::String::strFromAddr(a1), "bod1.xfbin")) {
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