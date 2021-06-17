#ifndef SETTINGS_H 
#define SETTINGS_H 
#pragma once

#include <string>

namespace moddingApi
{
	inline bool EnableConsole;
	inline int EnablePerfectStorm;
	inline bool EnableDebug;
	class Settings
	{
	public:
		static void ReadConfig(char *ConfigPath);

		static int LoadCpkInitial();
		static void AddCpk();
		static std::vector<const char*> CpkToLoad;
		static std::vector<int> CpkPriority;
	};

	struct cpkdata
	{
		const char* path;
		__int64 priority;
	};
}
#endif