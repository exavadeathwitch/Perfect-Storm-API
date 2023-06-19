#include "pch.hpp"

namespace prop {
	class functions {
	public:
		static signed __int64 __fastcall decreaseHealth(__int64 a1, __int64 a2, float Damage);
		static signed __int64 __fastcall decreaseChakra(__int64 a1, __int64 a2, float ChakraCost);
		static signed __int64 __fastcall decreaseSupportGaugeS(__int64 a1, __int64 a2, float SupportCost);
		static signed __int64 __fastcall decreaseSupportGaugeLS(__int64 a1, int a2, int Uselessvar, int NewSupportGaugeLevel);
		static __int64 __fastcall decreaseGuardHealth(__int64 a1, float GuardHealthSubtracted, int a3, int a4, int a5);
		static signed __int64 __fastcall decreaseSubs(__int64 a1, unsigned int a2, int Uselessvar, int NewSub);
		static signed __int64 __fastcall decreaseTools(__int64 a1, unsigned int a2, int MaxTool, int NewTool);
		static void __fastcall increaseStormGauge(__int64 BaseAddr, float Increment);
		static __int64 __fastcall CtrlGuardEffect(__int64 a1, int a2);
		static int __fastcall susanoojump(__int64 a1);
	};
}