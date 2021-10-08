#include "pch.hpp"

#include "Stage.hpp"

#include "Util/Memory/String.hpp"

#include <iostream>
void Stage::functions::getStageName(__int64 a1) {
	std::string initialName = util::memory::String::strFromAddrSpec(a1);
	if (initialName == "STAGE") {
		stageName = util::memory::String::strFromAddr(a1);
		std::cout << stageName << std::endl;
	}
}