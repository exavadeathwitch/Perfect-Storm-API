#include "pch.hpp"

#include "Camera.hpp"

#include "Util/Memory/Modify.hpp"

#include "Stage/Stage.hpp"

#include <iostream>

int __fastcall Camera::functions::writeFOVMenu(__int64 a1) {
	const auto retval = globals::hookManager->getOriginal<decltype(&Camera::functions::writeFOVMenu)>(Camera::functions::writeFOVMenu)(a1);
	if (Stage::stageName == "STAGE_TITLE_STAGE" || Stage::stageName == "STAGE_TITLE_R2B_STAGE") {
		__int64 baseAddr = a1 + 0x6C;
		*(float*)(baseAddr) = 65.0f;
		*(float*)(baseAddr + 0x8) = .034f;
		*(float*)(baseAddr + 0x10) = -17.0f;
		*(float*)(baseAddr + 0x18) = -.0922f;
		*(float*)(baseAddr + 0x1C) = 0.99594;
	}
	return retval;
}