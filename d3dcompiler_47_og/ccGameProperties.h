#pragma once

#include <stdio.h>
#include <string.h>

namespace moddingApi
{
	class ccGameProperties
	{
	public:
		static void DoGamePropertiesHook();
		static uintptr_t GlobalPointer;
		static void ReloadProperties();

		static void DoInitHook();
		static uintptr_t InitMemory;
		static void ReloadInit();

		static void DoAutoSaveHook();
		//static void ccLoadScene(std::string);

		static __int64 GetQword(__int64 qw);
		static int GetDword(__int64 dw);
		static __int64 GetOffset(__int64 of);
	};
}