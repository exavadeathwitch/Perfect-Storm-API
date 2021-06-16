#ifndef MAIN_H 
#define MAIN_H
#pragma once

#include <vector>
#include <WinSock2.h>
#include <Windows.h>
#include <string>

namespace moddingApi
{
	class Main
	{
	public:
		static DWORD WINAPI MainThread();
		static bool InitConfig();
		static std::string GetStormDirectory();
	};
}

#endif