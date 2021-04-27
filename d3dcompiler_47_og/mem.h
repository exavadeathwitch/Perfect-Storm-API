#ifndef INCLUDES_MEM
#define INCLUDES_MEM
/*----------------------------*/

#define INST_NOP            0x90
#define INST_CALL            0x08EB0000000215FF //Note: This is flipped around to how it appears in memory because x86 processors are little endian
#define INST_CALL_SIZE    16

typedef unsigned long long    u64;


namespace mem
{
    bool Hook(void* toHook, const void* myFnc, const u64 length = INST_CALL_SIZE);
    void TestHookOnline();
    //BYTE* TrampHook32(BYTE* src, BYTE* dst, const uintptr_t len);
}

/*----------------------------*/
#endif
