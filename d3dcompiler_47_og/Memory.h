#include <Windows.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

#include "CasualLibrary.hpp"


namespace moddingApi
{

	class Memory
	{
	public:
		static uintptr_t moduleBase;
		static Address CGbaseAddr;

		static __int64 GetQword(__int64 qw);
		static int GetDword(__int64 dw);
		static __int64 GetOffset(__int64 of);

		static void InitHooks();
		static void InitializeCasualLibrary();
	};
}