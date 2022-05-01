#pragma once

#include "pch.hpp"

namespace engine {
	inline bool runEngine = 1;
	class Engine {
	public:
		static int __fastcall gamelogic(DWORD* a1);
		static __int64 __fastcall pauseState(__int64 a1);
	};
}