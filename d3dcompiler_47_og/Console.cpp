#include <iostream>
#include <string>

#include "Console.h"
#include "Main.h"
#include "Memory.h"

//This function will initiate the console.
void moddingApi::Console::InitConsole() {

	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	std::cout << "----------Console Enabled----------" << std::endl;
}

void moddingApi::Console::LoopConsole() {
	bool loop = 1;
	std::string input;
	while (loop) {
		std::cout << ">";
		std::cin >> input;
		if (input == "1") {
			if (matchmakingFPS) {
				matchmakingFPS = 0;
			}
		}
	}
}