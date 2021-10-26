#pragma once

namespace Battle {
	inline bool inBattle = 0;
	inline bool onlineTraining = 0;
	DWORD matchCount = 0;
	class functions {
	public:
		static int __fastcall matchCount(__int64 rcx, __int64 a1, float a2);
		static __int64 __fastcall battleEnd(__int64 a1, int a2, __int64 a3, __int64 a4);
		static __int64 __fastcall loadDisconnectPopUp(__int64 a1);
	};
}