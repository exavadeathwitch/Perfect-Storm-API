#pragma once

namespace Net {
	inline int frameDelay;
	inline int nowCount;
	inline int matchmakingChannel = 1;
	class functions {
	public:
		static signed __int64 __fastcall calculateFrame(__int64 a1, int a2);
		static __int64 __fastcall randomNet(__int64 a1);
		static DWORD* __fastcall sub_140AEFEA0(__int64 a1, __int64 a2, int a3);
		static bool onOnline();
		static __int64 checkFPSMatchmaking();
	};
}