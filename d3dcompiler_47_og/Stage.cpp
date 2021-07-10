#include <iostream>
#include <string>

#include "Stage.h"
#include "Memory.h"
#include "Functions.h"


void moddingApi::Stage::getStageName(__int64 a1) {
	std::string_view initialName = moddingApi::Memory::strFromAddrSmall(a1);
	if ((initialName == "LTAGE_") || (initialName == "STAGE_")) {
		std::string_view stageName = moddingApi::Memory::strFromAddrMax(a1);
		//switch (moddingApi::Functions::str2int(stageName)) {
			/*
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62A"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD01B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD03B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD17B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
		case str2int("STAGE_SD62B"):
			std::cout << stageName << std::endl;
			break;
			*/
		//default:
			std::cout << stageName << std::endl; //break;
		}
	}