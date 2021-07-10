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

void enabletraining () {
	std::cout << "Training Enabled" << std::endl;
}

std::string Commands[4] = { "matchmakechannel", "enabletraining", "showvalues", "help" };
void moddingApi::Console::LoopConsole() {
	bool loop = 1;
	std::string input;
	while (loop) {
		std::cout << ">";
		std::cin >> input;
		for (int i = 0; i <= sizeof(Commands) - 1; i++) {
			if (Commands[i] == input) {
				
			}
		}
		if (input == "matchmakechannel") {
			std::cout << "Set matchmaking channel: ";
			std::cin >> matchmakingFPS;
			std::cout << "Channel is: " << matchmakingFPS << std::endl;
			}
		}
	}