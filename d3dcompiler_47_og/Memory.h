#ifndef MEMORY_H 
#define MEMORY_H

#include <Windows.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string>

inline int matchmakingFPS = 29;
namespace moddingApi
{

	class Memory
	{
	public:
		static uintptr_t moduleBase;
		static std::string strFromAddrSmall(__int64 a1);
		static std::string_view strFromAddrMax(__int64 a1);
		static __int64 GetQword(__int64 qw);
		static int GetDword(__int64 dw);
		static __int64 GetOffset(__int64 of);
		static __int64 getInfoFromMemoryString1(__int64 a1, int a2);

		static __int64 nnewPlayerState(__int64 a1, unsigned int a2, int a3, int a4);
		static void InitHooks();
		static void WriteBytes();

		template<std::size_t size>
		static auto read_bytes(const std::uintptr_t address)->std::array<std::uint8_t, size>;
		static __int64 nCDashANMTimer(__int64 a1, int a2);


		template <std::size_t size>
		static auto write_bytes(const std::uintptr_t start, const std::array<std::uint8_t, size>& bytes)-> bool;
	};
}
#endif