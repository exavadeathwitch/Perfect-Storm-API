#include "mem.h"
#include <Windows.h>
#include <vector>

bool mem::Detour32(BYTE* src, BYTE* dst, const uintptr_t len)
{
	if (len < 5) return false;

	DWORD curProtection;
	VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &curProtection);

	uintptr_t relativeAddress = dst - src - 5;

	*src = 0xE9;

	*(uintptr_t*)(src + 1) = relativeAddress;
	
	VirtualProtect(src, len, curProtection, &curProtection);

	return true;
}

BYTE* mem::TrampHook32(BYTE* src, BYTE* dst, const uintptr_t len)
{
	if (len < 5) return 0;

	//Create Gateway
	BYTE* gateway = (BYTE*)VirtualAlloc(0, len, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	//Write the Stolen Bytes to the Gateway
	memcpy_s(gateway, len, src, len);

	//Get the gateway to destination address
	uintptr_t gatewayRelativeAddr = src - gateway - 10;

	//Add the jmp opcode to the end of the gateway
	*(gateway + len) = 0xE9;

	//Write the address of the gateway to the jmp
	*(uintptr_t*)((uintptr_t)gateway + len + 1) = gatewayRelativeAddr;

	//Perform the detour
	mem::Detour32(src, dst, len);

	return gateway;
}
