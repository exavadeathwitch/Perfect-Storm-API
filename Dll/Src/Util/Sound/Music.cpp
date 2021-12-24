#include "pch.hpp"

#include "Music.hpp"

#include "SDL2Music.h"

#include "General/general.hpp"

#include "GameSettings/gameSettings.hpp"

#include "Stage/Stage.hpp"

#include "Net/net.hpp"

#include "Battle/battle.hpp"

#include <string>

#include <filesystem>

#include <iostream>

#include <time.h>

void music::functions::playMusicTrackTest() {
	SDL2Music music;
	std::string dirpath = General::defaultFilepath + "\\sound\\test";
	std::string str_obj(dirpath);
	char* dirpath_arr = &str_obj[0];

	srand(time(NULL));

	int numtracks = 0;
	for (const auto& file : std::filesystem::directory_iterator(dirpath)) {

		music.addMusicTrack(file.path().string().c_str());
		numtracks++;
	}
	Mix_VolumeMusic(gameSettings::musicVol / 1.25);
	//std::cout << gameSettings::musicVol << std::endl;
	//std::cout << gameSettings::musicVol / 1.25 << std::endl;
	music.playMusicTrack(rand() % numtracks);
}

void music::functions::playStageMusicTrack() {
	SDL2Music music;
	std::string stageName = Stage::fbStageName.erase(0, 2);
	std::string dirpath = General::defaultFilepath + "\\sound\\music\\stage\\" + stageName;
	std::string str_obj(dirpath);
	char* dirpath_arr = &str_obj[0];
	//std::cout << dirpath << std::endl;
	srand(time(NULL));

	int numtracks = 0;
	for (const auto& file : std::filesystem::directory_iterator(dirpath)) {
		
		music.addMusicTrack(file.path().string().c_str());
		numtracks++;
	}
	Mix_VolumeMusic(gameSettings::musicVol / 1.25);
	if (gameSettings::musicVol == 0)
		Mix_VolumeMusic(0);
	music.playMusicTrack(rand() % numtracks);
}

void music::functions::playMenuMusicTrack(int trackNum) {
	std::string menuDir = "";
	SDL2Music music;
	//std::cout << "Track Number: " << trackNum << std::endl;
	//if ((-1 < trackNum < 4) && (Battle::inBattle == 0) && (Battle::matchCount > 0))
		//return;
	//std::cout << "post switch" << std::endl;
	switch (trackNum) {
	case 0:
		menuDir = "Main Menu";
		break;
	case 1:
		menuDir = "Online Lobby";
		break;
	case 2:
		menuDir = "Character Select";
		break;
	case 3:
		menuDir = "Character Select";
		break;
	case 4:
		menuDir = "Win Screen";
		util::memory::Modify::write_bytes<5>(globals::moduleBase + 0xA4357B + 0xC00, { 0xE8, 0x9C, 0xAC, 0x5D, 0xFF });
		break;
	default:
		return;
		break;
	}

	music.Halt_Music();
	std::string dirpath = General::defaultFilepath + "\\sound\\music\\menu\\" + menuDir;
	std::string str_obj(dirpath);
	char* dirpath_arr = &str_obj[0];
	//std::cout << dirpath << std::endl;
	srand(time(NULL));

	int numtracks = 0;
	for (const auto& file : std::filesystem::directory_iterator(dirpath)) {

		music.addMusicTrack(file.path().string().c_str());
		numtracks++;
	}
	//std::cout << gameSettings::musicVol << std::endl;
	Mix_VolumeMusic(gameSettings::musicVol / 1.25);
	if (gameSettings::musicVol == 0)
		Mix_VolumeMusic(0);
	music.playMusicTrack(rand() % numtracks);
}
/*
void music::functions::PauseResumeMusicTrack() {
	SDL2Music music;
	music.Play_Pause();
}
*/