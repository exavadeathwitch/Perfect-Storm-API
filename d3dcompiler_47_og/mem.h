#include <Windows.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
namespace mem
{
    void InitializeCasualLibrary();
    bool Detour32(BYTE* src, BYTE* dst, const uintptr_t len);
    void PerfectStormHook();
    void GeneralHook();
    BYTE* TrampHook32(BYTE* src, BYTE* dst, const uintptr_t len);
    void __fastcall nSetRoomName(__int64 BaseLobbyAddr);
    __int64 __fastcall nDecreaseHealth(__int64 a1, __int64 a2, float Damage);
    __int64 __fastcall nDecreaseChakra(__int64 a1, __int64 a2, float ChakraCost);
    signed __int64 __fastcall nDecreaseSupportGaugeS(__int64 a1, __int64 a2, float SupportCost);
    signed __int64 __fastcall nDecreaseSupportGaugeLS(__int64 a1, int a2, int Uselessvar, int NewSupportGaugeLevel);
    __int64 __fastcall nDecreaseGuardHealth(__int64 a1, float GuardHealthSubtracted, int a3, int a4, int a5);
    signed __int64 __fastcall nDecreaseSubs(__int64 a1, unsigned int a2, int Uselessvar, int NewSub);
    signed __int64 __fastcall nDecreaseTools(__int64 a1, unsigned int a2, int MaxTool, int NewTool);
    void __fastcall nIncreaseStormGauge(__int64 BaseAddr, float Increment);
    int __fastcall nSetStormGaugeto0(__int64 a1);
    void __fastcall nfc_ccGetCurrentStageName(__int64 a1);
    //__declspec(naked) int nleaderChange(__int64 a1, __int64 a2, __int64 a3, __int64 a4);
}