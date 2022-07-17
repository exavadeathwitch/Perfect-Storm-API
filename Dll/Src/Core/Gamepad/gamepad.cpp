#include "pch.hpp"

#include "gamepad.hpp"

#include "Core/Engine/engine.hpp"

#include "Core/Online/online.hpp"

#include "imgui/include/imgui.h"

#include "half/half.hpp"

#include <iostream>
int __fastcall S1API::gamepad::gamepadLoop(__int64 a1)
{
    typedef int(__fastcall* sub_1401396B0) (__int64 a1);
    sub_1401396B0 osub_1401396B0 = (sub_1401396B0)(globals::moduleBase + 0x138AB0 + 0xC00);
    __int64 v1; // rsi@1
    __int64 v2; // rbx@3
    __int64 v3; // rdi@3
    signed __int64 v4; // rbp@3
    int result; // eax@4

    v1 = a1;
    if (*(BYTE*)(a1 + 16))
        osub_1401396B0(a1);
    v2 = 0i64;
    v3 = 0i64;
    v4 = 4i64;
    result = 0;
    do
    {
        result = (*(int(__fastcall**)(__int64))(*(__int64*)(v2 + *(__int64*)(v1 + 8)) + 48i64))(v3 + *(__int64*)(v1 + 8));
        v3 += 392i64;
        v2 += 392i64;
        --v4;
    } while (v4);
    return result;
}

signed __int64 __fastcall S1API::gamepad::getPadAddr(__int64 a1, signed int padNum, int a3) {
    DWORD* v3; // r10@1
    signed int v4; // er9@1
    __int64 v5; // rax@9
    __int64 retval = globals::hookManager->callOriginal<decltype(&S1API::gamepad::getPadAddr)>(S1API::gamepad::getPadAddr, a1, padNum, a3);
    return retval;
    //std::cout << std::hex << &S1API::hostpad << std::dec << std::endl;
    if (padNum == 0) {
        S1API::pad pad = *reinterpret_cast<S1API::pad*>(retval);
        S1API::hostpad.InstantInput = pad.InstantInput; // 4 Bytes
        S1API::hostpad.ReleaseInput = pad.ReleaseInput; // 4 Bytes
        S1API::hostpad.HeldInput = pad.HeldInput; // 4 Bytes
        S1API::hostpad.leftanalogup = pad.leftanalogup; // 2 Bytes
        S1API::hostpad.leftanalogdown = pad.leftanalogdown; // 2 Bytes
        S1API::hostpad.leftanalogleft = pad.leftanalogleft; // 2 Bytes
        S1API::hostpad.leftanalogright = pad.leftanalogright; // 2 Bytes
        S1API::hostpad.rightanalogup = pad.rightanalogup; // 2 Bytes
        S1API::hostpad.rightanalogdown = pad.rightanalogdown; // 2 Bytes
        S1API::hostpad.rightanalogleft = pad.rightanalogleft; // 2 Bytes
        S1API::hostpad.rightanalogright = pad.rightanalogright; // 2 Bytes
        //S1API::hostpad.lefttriggerpressed = pad.lefttriggerpressed;
        //S1API::hostpad.righttriggerpressed = pad.righttriggerpressed;
        return (__int64)&S1API::hostpad;
    }
    if (engine::inBattle == 1 && S1API::enableOnline == 1) {
        if (0 <= padNum <= 1) {
            if (*(DWORD*)(retval + 0x10) == 8)
                *(DWORD*)(retval + 0x10) -= 8;
            if (*(DWORD*)(retval + 0x14) == 8)
                *(DWORD*)(retval + 0x14) -= 8;
            if (*(DWORD*)(retval + 0x18) == 8)
                *(DWORD*)(retval + 0x18) -= 8;
        }
    }
    return retval;
}

