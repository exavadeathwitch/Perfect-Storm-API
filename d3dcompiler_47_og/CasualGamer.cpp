#include <stdio.h>
#include <iostream>
#include "Memory.h"
#include "ManageMemory.h"

void ManageMemory::CasualGamer::InitializeMemory()
{
	NSUNS4memory = External::Memory("NSUNS4.exe", true);
	//std::cout << "Casual Gamer Memory Initalized" << std::endl;
}

void ManageMemory::CasualGamer::GetClientAddress()
{
	//clientAddr = Internal::Memory::getModule("d3dcompiler_47_o.dll");
	//clientAddr = NSUNS4memory.getModule("d3dcompiler_47.dll");
	std::cout << clientAddr << std::endl;
	std::cout << "Casual Gamer Client Address Obtained" << std::endl;
}