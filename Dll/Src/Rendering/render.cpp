#include "pch.hpp"

#include "render.hpp"


std::vector<__int64> testVector;
int __fastcall render::Render::renderElements(__int64 a1, signed __int64 a2, unsigned int a3, int a4)
{
    int result; // eax@1
    int v5; // ebp@1
    __int64 v6; // rsi@3
    __int64 v7; // r15@6
    __int64** v8; // r14@6
    __int64* v9; // rdi@7
    __int64 v10; // rbx@7
    int v11; // edx@8
    __int64***** v12; // rdx@10
    __int64*** v13; // rcx@10
    __int64**** v14; // rdx@11
    unsigned __int64 v15; // r8@18
    __int64** v16; // rax@14
    __int64 v17; // rdx@16

    typedef __int64(__fastcall* sub_14053C910) (__int64 a1, int a2);
    sub_14053C910 osub_14053C910 = (sub_14053C910)(globals::moduleBase + 0x53BD10 + 0xC00);

    result = 127;
    v5 = a4;
    if ((unsigned int)a2 >= 0x80)
        a2 = 127i64;
    v6 = a1;
    if (a3 >= 0x80)
        a3 = 127;
    if ((unsigned int)a2 <= a3)
    {
        result = a2;
        v7 = a3 - (unsigned int)a2 + 1;
        v8 = (__int64**)(a1 + 8 * ((unsigned int)a2 + 4 * a2 + 3));
        do
        {
            v9 = *v8;
            v10 = **v8;
            if ((__int64*)v10 != *v8)
            {
                do
                {
                    v11 = 0;
                    if (*(__int64*)(v6 + 5176) && v5)
                    {
                        v12 = *(__int64******)(v6 + 5144);
                        v13 = 0i64;
                        if (v12)
                        {
                            v14 = *v12;
                            if (v14)
                                v13 = *v14;
                        }
                        if (v13 && (v16 = *v13) != 0i64 && *v16)
                            v17 = **v16;
                        else
                            v17 = 0i64;
                        v15 = *(__int64*)(v6 + 0x1430) + *(__int64*)(v6 + 5176) - 1i64;
                        v11 = *(DWORD*)(*(__int64*)(*(__int64*)(v17 + 8) + 8 * ((*(__int64*)(v17 + 16) - 1i64) & (v15 >> 2)))
                            + 4 * (v15 & 3));
                    }
                    if (std::find(testVector.begin(), testVector.end(), *(__int64*)(v10 + 16)) == testVector.end()) {
                        testVector.push_back(*(__int64*)(v10 + 16));
                    }
                    if (render::uiOn == 0) {
                        for (int i = 0; i < testVector.size(); i++) {
                            if ((testVector[i] == *(__int64*)(v10 + 16)) && ((i) == 0))
                                result = osub_14053C910(*(__int64*)(v10 + 16), v11);
                            if ((testVector[i] == *(__int64*)(v10 + 16)) && ((i) == 1))
                                result = osub_14053C910(*(__int64*)(v10 + 16), v11);
                            if ((testVector[i] == *(__int64*)(v10 + 16)) && ((i) == 2))
                                result = osub_14053C910(*(__int64*)(v10 + 16), v11);
                            if ((testVector[i] == *(__int64*)(v10 + 16)) && ((i) == 3))
                                result = osub_14053C910(*(__int64*)(v10 + 16), v11);
                            if ((testVector[i] == *(__int64*)(v10 + 16)) && ((i) == 4))
                                result = osub_14053C910(*(__int64*)(v10 + 16), v11);
                            if ((testVector[i] == *(__int64*)(v10 + 16)) && ((i) == 5))
                                result = osub_14053C910(*(__int64*)(v10 + 16), v11);
                            if ((testVector[i] == *(__int64*)(v10 + 16)) && ((i) == 6))
                                result = osub_14053C910(*(__int64*)(v10 + 16), v11);
                            if ((testVector[i] == *(__int64*)(v10 + 16)) && ((i) == 7))
                                result = osub_14053C910(*(__int64*)(v10 + 16), v11);
                            if ((testVector[i] == *(__int64*)(v10 + 16)) && ((i) == 8))
                                result = osub_14053C910(*(__int64*)(v10 + 16), v11);
                            if ((testVector[i] == *(__int64*)(v10 + 16)) && ((i) == 9))
                                result = osub_14053C910(*(__int64*)(v10 + 16), v11);
                            if ((testVector[i] == *(__int64*)(v10 + 16)) && ((i) == 11))
                                result = osub_14053C910(*(__int64*)(v10 + 16), v11);
                            if ((testVector[i] == *(__int64*)(v10 + 16)) && ((i) == 12))
                                result = osub_14053C910(*(__int64*)(v10 + 16), v11);
                            if ((testVector[i] == *(__int64*)(v10 + 16)) && ((i) == 13))
                                result = osub_14053C910(*(__int64*)(v10 + 16), v11);
                            if ((testVector[i] == *(__int64*)(v10 + 16)) && ((i) == 15))
                                result = osub_14053C910(*(__int64*)(v10 + 16), v11);
                            if ((testVector[i] == *(__int64*)(v10 + 16)) && ((i) == 16))
                                result = osub_14053C910(*(__int64*)(v10 + 16), v11);
                        }
                    }
                    else
                        result = osub_14053C910(*(__int64*)(v10 + 16), v11);
                    v10 = *(__int64*)v10;
                } while ((__int64*)v10 != v9);
            }
            v8 += 5;
            --v7;
        } while (v7);
    }
    return 2;
}
