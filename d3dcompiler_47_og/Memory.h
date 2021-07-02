#include <Windows.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string>

inline bool matchmakingFPS = 0;
namespace moddingApi
{

	class Memory
	{
	public:
		static uintptr_t moduleBase;

		static __int64 GetQword(__int64 qw);
		static int GetDword(__int64 dw);
		static __int64 GetOffset(__int64 of);
		static __int64 getInfoFromMemoryString1(__int64 a1, int a2);
		static __int64 nInitializeccSceneBootRoot(__int64 a1);
		static __int64 nInitializeccSceneFreeBattleBegin(BYTE* a1);
		static __int64 nInitializeccSceneBattleModeSelect(__int64 a1);
		static __int64 nnewPlayerState(__int64 a1, unsigned int a2, int a3, int a4);
		static void InitHooks();
		static void WriteBytes();

		template <std::size_t size>
		static auto write_bytes(const std::uintptr_t start, const std::array<std::uint8_t, size>& bytes)-> bool;
	};
}