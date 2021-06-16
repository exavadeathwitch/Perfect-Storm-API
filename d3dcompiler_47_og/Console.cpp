#include <iostream>
#include <string>

#include "Console.h"
#include "Main.h"

//This function will initiate the console.
void moddingApi::Console::InitConsole() {

	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	std::cout << "----------Console Enabled----------" << std::endl;
}

void moddingApi::Console::LoopConsole() {

}