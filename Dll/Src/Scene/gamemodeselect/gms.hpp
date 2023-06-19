#pragma once

#include "pch.hpp"

#include <string>
namespace gms {
    inline int gamefunc = 0;
    inline int currentmenu;
    class functions {
    public:
        static __int64 readMenuChange(__int64 a1, BYTE* a2, int* a3, __int64 a4);
        static __int64 __fastcall sub_140DA0130(int* a1, __int64 a2, __int64 a3, __int64 a4);
    };
}