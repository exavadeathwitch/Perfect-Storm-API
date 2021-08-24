#ifndef STAGE_H 
#define STAGE_H

#include <Windows.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string>


inline std::string stageName;
namespace moddingApi
{
	class Stage
	{
	public:
		static void stageHooks();
		static void getStageName(__int64 a1);
	};
}
#endif