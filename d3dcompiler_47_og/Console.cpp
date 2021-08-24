#include <iostream>
#include <string>
#include <SDL.h>

#include "Console.h"
#include "Main.h"
#include "Memory.h"
#include "Music.h"
#include "SDL2/SDL2Music.h"
#include "SDL2/SDLInit.h"
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

		if (input == "MusicToggle") {
			moddingApi::Music::PlayMusicTrackTest();
		}
		if (input == "MusicPause") {
			moddingApi::Music::PauseResumeMusicTrack();
		}
		if (input == "MusicStop") {
			Mix_HaltMusic();
		}
		if (input == "MusicVol") {
			int vol;
			std::cout << "Volume" << std::endl;
			std::cin >> vol;
			Mix_VolumeMusic(vol);
		}
	}
}