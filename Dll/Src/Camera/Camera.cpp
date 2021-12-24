#include "pch.hpp"

#include "Camera.hpp"

#include "Util/Memory/Modify.hpp"

#include "Stage/Stage.hpp"

#include <iostream>

int __fastcall Camera::functions::writeFOVMenu(__int64 a1) {
	const auto retval = globals::hookManager->getOriginal<decltype(&Camera::functions::writeFOVMenu)>(Camera::functions::writeFOVMenu)(a1);
	__int64 baseAddr = a1 + 0x6C;
	if (Stage::stageName == "STAGE_TITLE_STAGE" || Stage::stageName == "STAGE_TITLE_R2B_STAGE") {

		*(float*)(baseAddr) = 65.0f;
		*(float*)(baseAddr + 0x8) = .034f;
		*(float*)(baseAddr + 0x10) = -17.0f;
		*(float*)(baseAddr + 0x18) = -.0922f;
		*(float*)(baseAddr + 0x1C) = 0.99594f;

		if (*(float*)(baseAddr + 0x20) == -647.3275757f) {
			Camera::lockTitle = 1;
		}
		//std::cout << Camera::lockTitle << std::endl;
		if (Camera::lockTitle == 1) {
			*(float*)(baseAddr + 0x4) = 0.9994146824f;
			*(float*)(baseAddr + 0x8) = 0.034f;
			*(float*)(baseAddr + 0xC) = 3.088616268E-6f;
			*(float*)(baseAddr + 0x10) = -17.0f;
			*(float*)(baseAddr + 0x14) = 0.003106977325f;
			*(float*)(baseAddr + 0x18) = -.0922f;
			*(float*)(baseAddr + 0x1C) = 0.99594f;
			*(float*)(baseAddr + 0x20) = -647.3275757f;
			*(float*)(baseAddr + 0x24) = 0.03407210112f;
		}
	}
	return retval;
}