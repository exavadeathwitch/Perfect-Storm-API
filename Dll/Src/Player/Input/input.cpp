#include "pch.hpp"

#include "input.hpp"

int input::functions::applyPlayerInput(__int64 baseAddr) {

	__int64 inputPointer = baseAddr + 0x218;
	const auto retval = globals::hookManager->callOriginal<decltype(&input::functions::applyPlayerInput)>(input::functions::applyPlayerInput, baseAddr);
	if (*(DWORD*)(baseAddr + 0xCC0) == 154) {
		if (*(DWORD*)(baseAddr + 0xCC4) == 74) {
				*(uint8_t*)(inputPointer + 0x407) = 0;
				*(uint8_t*)(inputPointer + 0x407) = 0;
				*(float*)(baseAddr + 0x1B0 + 0x108 + 0x70) = 0;
				*(uint8_t*)(baseAddr + 0x1B9 + 0x108 + 0x70) = 0;
				*(uint8_t*)(inputPointer + 0x40F) = 0;
		}
	}

	if (*(DWORD*)(baseAddr + 0xCC0) == 153) {
		*(uint8_t*)(inputPointer + 0x407) = 0;
		*(uint8_t*)(inputPointer + 0x407) = 0;
		*(float*)(baseAddr + 0x1B0 + 0x108 + 0x70) = 0;
		*(uint8_t*)(baseAddr + 0x1B9 + 0x108 + 0x70) = 0;
		*(uint8_t*)(inputPointer + 0x40F) = 0;
	}
	bool stuffRan = 0;
	if (*(uint8_t*)(inputPointer + 0x408) == *(uint8_t*)(inputPointer + 0x599) && *(float*)(baseAddr + 0x1B0 + 0x70) > 0.0f) {
		*(float*)(baseAddr + 0x1B0 + 0x70) = .3f;
		stuffRan = 1;
	}
	if (*(uint8_t*)(inputPointer + 0x40A) == 0 && stuffRan == 1) {
		*(float*)(baseAddr + 0x1B0 + 0x70) = 0.0f;
	}
	return retval;
}
