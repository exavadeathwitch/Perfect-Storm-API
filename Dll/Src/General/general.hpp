#pragma once

#include "pch.hpp"

#include <string>
namespace General {
	std::vector<const char*> CpkToLoad;
	std::vector<int> CpkPriority;
	std::string defaultFilepath = ".\\Perfect Storm\\";
	class functions {
	public:
		static __int64 __fastcall getMemString(__int64 a1, int a2);
		static int __fastcall noMusicTrack(__int64 a1, __int64 a2, __int64 a3);
		static signed __int64 __fastcall musicTrack(__int64 a1, __int64 a2, int a3);
		static signed __int64 __fastcall makeGameFocus(__int64 a1);
		static signed __int64 __fastcall makeGameNotFocus(__int64 a1);
		static const char* retTitleVer();
		static int loadCpkInitial();
	};
	struct cpkdata
	{
		const char* path;
		__int64 priority;
	};
}