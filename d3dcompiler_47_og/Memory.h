#include <Windows.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string>
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
		static void moddingApi::Memory::WriteBytes();

		template <std::size_t size>
		static auto write_bytes(const std::uintptr_t start, const std::array<std::uint8_t, size>& bytes)-> bool;
	};
}