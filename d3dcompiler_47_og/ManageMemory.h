#pragma once
#include "Memory.h"
static External::Memory NSUNS4memory = External::Memory("NSUNS4.exe");
static Address clientAddr;


namespace ManageMemory
{
	class CasualGamer
	{
	public:
		static void InitializeMemory();
		static void GetClientAddress();
	};
}