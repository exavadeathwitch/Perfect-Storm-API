#pragma once

class ccPlayerSupport
{
	public:
		static __int64* RequestSupportAction(float a1, int a2, __int64 a3);
};

namespace misc
{
	uint8_t __fastcall getSupportAction(__int64 a1);
}