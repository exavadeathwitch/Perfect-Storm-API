#ifndef CONSOLE_H
#define CONSOLE_H
#pragma once

#include <vector>
#include <WinSock2.h>
#include <Windows.h>

namespace moddingApi
{
	class Console
	{
	public:
		static void InitConsole();
		static void LoopConsole();
	};
}

#endif