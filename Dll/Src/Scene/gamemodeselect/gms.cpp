#include "pch.hpp"

#include "gms.hpp"
__int64 __fastcall gms::functions::sub_140DA0130(int* a1, __int64 a2, __int64 a3, __int64 a4) {
	gms::gamefunc = 1;
	return globals::hookManager->callOriginal<decltype(&gms::functions::sub_140DA0130)>(gms::functions::sub_140DA0130, a1, a2, a3, a4);
}
__int64 gms::functions::readMenuChange(__int64 a1, BYTE* a2, int* a3, __int64 a4) {
	std::cout << *(DWORD*)(a1 + 0x4) << std::endl;
	if (*(DWORD*)(a1 + 0x4) == 0xC8 && gms::gamefunc == 1) {
		std::cout << "hooray\n";
		*(DWORD*)(a4 + 0xC8) = 0;
	}
	return globals::hookManager->callOriginal<decltype(&gms::functions::readMenuChange)>(gms::functions::readMenuChange, a1, a2, a3, a4);
}