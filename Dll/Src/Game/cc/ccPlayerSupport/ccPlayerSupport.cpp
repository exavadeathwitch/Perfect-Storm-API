#include "pch.hpp"

#include "Game/misc/misc.hpp"

#include "ccPlayerSupport.hpp"

int returnval = 0;
__int64* ccPlayerSupport::RequestSupportAction(float a1, int a2, __int64 a3) {
	returnval = 1;
	auto retval = globals::hookManager->getOriginal<decltype(&ccPlayerSupport::RequestSupportAction)>(ccPlayerSupport::RequestSupportAction)(a1, a2, a3);
	returnval = 0;
	return retval;
}

uint8_t misc::getSupportAction(__int64 a1)
{
	auto retval = globals::hookManager->callOriginal<decltype(&misc::getSupportAction)>(misc::getSupportAction, a1);
	if (returnval == 1)
		std::cout << (int)retval << std::endl;
	return retval;
}