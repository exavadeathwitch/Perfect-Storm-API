#include "mem.h"
#include <Windows.h>


bool mem::Hook(void* toHook, const void* myFnc, const u64 length)
{
    if (toHook && myFnc)
    {
        if (length < INST_CALL_SIZE)
            return false;

        DWORD curProtection;
        VirtualProtect(toHook, length, PAGE_EXECUTE_READWRITE, &curProtection);

        if (length > INST_CALL_SIZE)
            memset(toHook, INST_NOP, length);

        *(u64*)toHook = INST_CALL;
        *(u64*)((u64)toHook + 8) = (u64)myFnc;

        DWORD temp;
        VirtualProtect(toHook, length, curProtection, &temp);

        return true;
    }
    else
    {
        return false;
    }
}
/*
BYTE* mem::TrampHook32(BYTE* src, BYTE* dst, const uintptr_t len)
{
	if (len < 10) return 0;

	//Create Gateway
	BYTE* gateway = (BYTE*)VirtualAlloc(0, len, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	//Write the Stolen Bytes to the Gateway
	memcpy_s(gateway, len, src, len);

	//Get the gateway to destination address
	uintptr_t gatewayRelativeAddr = src - gateway - 10;

	//Add the jmp opcode to the end of the gateway
	*(gateway + len) = 0x25FF;

	//Write the address of the gateway to the jmp
	*(uintptr_t*)((uintptr_t)gateway + len + 1) = gatewayRelativeAddr;

	//Perform the detour
	mem::Hook(src, dst, len);

	return gateway;
}
*/