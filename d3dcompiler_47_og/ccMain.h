#ifndef CCMAIN_H 
#define CCMAIN_H
#pragma once

#include <vector>
#include <WinSock2.h>
#include <Windows.h>

namespace moddingApi
{
	class ccMain
	{
	public:
		static DWORD WINAPI Main();
	};
}

#endif