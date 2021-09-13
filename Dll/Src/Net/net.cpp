#include "pch.hpp"

#include "net.hpp"

#include <iostream>

signed __int64 __fastcall Net::functions::calculateFrame(__int64 a1, int a2) {
	__int64 retval = globals::hookManager->callOriginal<decltype(&Net::functions::calculateFrame)>(Net::functions::calculateFrame, a1, a2);
	return retval;
	int v3 = *(DWORD*)(a1 + 0x1D010);
	int v4 = *(DWORD*)(a1 + 0x1D014);
	int v5 = *(DWORD*)(retval);
	if (retval != 0) {
		//std::cout << "a1: " << std::hex << a1 << std::endl;
		//std::cout << "a2: " << std::dec << a2 << std::endl;
		
		std::cout << "v3: " << std::dec << v3 << std::endl;
		std::cout << "v4: " << std::dec << v4 << std::endl;
		std::cout << "v5: " << std::dec << v5 << std::endl;
		/*
		if ((something - a2) == (something - **(DWORD**)&retval)) {
			if ((something - a2) <= 1) {
				return retval;
			}
			netFrame = something - a2;
			if (netFrame <= 1)
				return retval;
			//printf("netFrame: %d\n", netFrame);
		}
	*/
	}

	return retval;
}

__int64 __fastcall Net::functions::randomNet(__int64 a1) {
	__int64 retval = globals::hookManager->callOriginal<decltype(&Net::functions::randomNet)>(Net::functions::randomNet, a1);
	Net::nowCount = *(DWORD*)(a1 + 0x3C);
	return retval;
}

DWORD* __fastcall Net::functions::sub_140AEFEA0(__int64 a1, __int64 a2, int a3)
{
	DWORD* result;

	result = (DWORD*)globals::hookManager->callOriginal<decltype(&Net::functions::calculateFrame)>(Net::functions::calculateFrame, a1 + 0xC, *(DWORD*)(a1 + 4));
	if (result)
	{
		if (Net::nowCount - *result > 0)
			Net::frameDelay = Net::nowCount - *result - 1;
	}
	DWORD* retVal = globals::hookManager->callOriginal<decltype(&Net::functions::sub_140AEFEA0)>(Net::functions::sub_140AEFEA0, a1, a2, a3);
	return retVal;
}

bool Net::functions::onOnline() {
	if (*(DWORD*)(globals::moduleBase + 0x1608D40) >= 1)
		return 1;
	return 0;
}