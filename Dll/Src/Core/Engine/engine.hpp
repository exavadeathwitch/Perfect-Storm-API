#pragma once

#include "pch.hpp"

namespace engine {
	inline bool runEngine = 1;
	inline bool inBattle = 0;
	inline bool charsel = 0;
	inline bool triggerMenu = 0;
	class Engine {
	public:
		static int __fastcall battleStart(__int64 a1, int a2);
		static int __fastcall outBattle(__int64 a1);
		static __int64 __fastcall initCharsel(__int64 a1);
		static int __fastcall menuControl(__int64 a1);
		static int __fastcall gamelogic(DWORD* a1);
		static __int64 __fastcall pauseState(__int64 a1);
		static signed __int64 __fastcall loadText(__int64 a1);
		static DWORD* __fastcall initStuff(__int64* a1, __int64 a2, __int64 a3);
		static __int64* __fastcall enableWindow(__int64* a1, __int64 a2);
		static __int64 __fastcall ccGameManager_Play(__int64 a1);
		static __int64 __fastcall LoadExpectedScene(__int64 a1, int a2);
		static signed __int64 __fastcall MainProcess(__int64 a1);
		static signed __int64 __fastcall gameduelmain(__int64 a1);
		static int __fastcall resultsignal(__int64 a1);
		static int __fastcall withoutwin(__int64 a1);
	};
}