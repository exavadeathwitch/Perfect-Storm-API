#include "pch.hpp"

#include "Framework.hpp"

#include "Core/SDK/Game.hpp"

#include "Game/ccTaskManager/ccTaskManager.hpp"

#include "Core/DebugMenu/DebugMenu.hpp"
int __fastcall Framework::MainLoop(__int64 a1) {
    ro.rosterrunning = 0;
    mainlooppointer = a1;
    return globals::hookManager->callOriginal<decltype(&Framework::MainLoop)>(Framework::MainLoop, a1);
    /*
    * typedef char(__fastcall* checkSystemCallback) ();
checkSystemCallback ocheckSystemCallback = (checkSystemCallback)(globals::moduleBase + 0xA08C10 + 0xC00);


typedef signed __int64(__fastcall* pushBlock) (int a1);
pushBlock opushBlock = (pushBlock)(globals::moduleBase + 0xA01080 + 0xC00);


typedef __int64(__fastcall* update) (__int64 a1);
update oUpdate = (update)(globals::moduleBase + 0xADF9D0 + 0xC00);


typedef __int64(__fastcall* sceneexecute) (__int64 a1);
sceneexecute osceneexecute = (sceneexecute)(globals::moduleBase + 0xAB4C10 + 0xC00);


typedef __int64(__fastcall* PopBlock) ();
PopBlock oPopBlock = (PopBlock)(globals::moduleBase + 0xA01050 + 0xC00);


typedef int(__fastcall* n) (__int64 a1);
n nUpdate = (n)(globals::moduleBase + 0xA0B980 + 0xC00);

        __int64 v2; // rcx
        unsigned int v3; // r8d
        __int64 v4; // rdx
        int result; // eax

    do
    {
        ocheckSystemCallback();
        pushBlock(1);
        ccTaskManager::Execute((__int64*)(a1 + 80), 0i64, 1u, 0);
        if (*(DWORD*)(a1 + 276))
        {
            if (*(DWORD*)(a1 + 280))
                goto LABEL_7;
        LABEL_5:
            v4 = 0x50i64;
            v3 = 128;
            goto LABEL_6;
        }
        if (!*(DWORD*)(a1 + 280))
            goto LABEL_5;
        oUpdate(*(__int64*)(a1 + 152));

        sceneexecute((__int64*)(a1 + 72));
        ccTaskManager::Execute((__int64*)(a1 + 80), 2i64, 0x4Fu, 1);// nonrender
        v3 = -1;
        v4 = 0x55i64;
    LABEL_6:
        ccTaskManager::Execute((__int64*)(a1 + 80), v4, v3, 1);// render
        //result = nUpdate(globals::moduleBase + 0x16663C8);
    LABEL_7:
        //ccTaskManager::Execute((__int64*)(a1 + 80), v4, v3, 1);// render
        oPopBlock();
        result = nUpdate(globals::moduleBase + 0x16663C8);
    }
    while (*(DWORD*)(a1 + 0x40));
    return result;*/
}