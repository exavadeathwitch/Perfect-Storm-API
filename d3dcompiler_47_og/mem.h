#include <Windows.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
namespace mem
{
    bool Detour32(BYTE* src, BYTE* dst, const uintptr_t len);
    int TestHookOnline();
    BYTE* TrampHook32(BYTE* src, BYTE* dst, const uintptr_t len);
    void __fastcall nSetRoomName(__int64 BaseLobbyAddr);
    //__declspec(naked) int nleaderChange(__int64 a1, __int64 a2, __int64 a3, __int64 a4);
}