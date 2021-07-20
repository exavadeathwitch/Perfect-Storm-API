#include <iostream>
#include <string>

#include "Stage.h"
#include "Memory.h"
#include "Functions.h"


void moddingApi::Stage::getStageName(__int64 a1) {
	std::string initialName = moddingApi::Memory::strFromAddrSmall(a1);
	if ((initialName == "LTAGE_") || (initialName == "STAGE_")) {
		std::string_view stageName = moddingApi::Memory::strFromAddrMax(a1);
		std::cout << stageName << std::endl;
	}
}