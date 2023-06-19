#pragma once

#include "pch.hpp"

#include <string>
namespace Scene {
    inline std::string ccScene = "null";
    class functions {
    public:
    static __int64 __fastcall loadccSceneNetworkSessionCreate_New(__int64 a1);
    static __int64 __fastcall loadccSceneNetworkSessionSearch_New(__int64 a1);
    static __int64 __fastcall loadccSceneNetworkMenu_New(__int64 a1);
    static __int64 __fastcall ccSceneTitle(__int64 a1);
    static __int64 __fastcall ccSceneBootLogo(__int64 a1);
    static __int64 __fastcall ccSceneFreeBattle(__int64 a1);
    static __int64 __fastcall ccSceneFreeBattleCharacterSelect(__int64 a1);
    static __int64 __fastcall ChangeCore(__int64 a1);
    };
}