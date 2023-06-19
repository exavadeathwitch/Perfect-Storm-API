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
	//music.playMusicTrack(rand() % numtracks, 1);
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
	std::string pathone = General::defaultFilepath + "\\sound\\music\\menu\\" + "Main Menu";
	std::string pathtwo = General::defaultFilepath + "\\sound\\music\\menu\\" + "Game Mode Select";
	std::string paththree = General::defaultFilepath + "\\sound\\music\\menu\\" + "Character Select";
	for (const auto& file : std::filesystem::directory_iterator(dirpath)) {
		music.addChunk(file.path().string().c_str());
		music.addMusicTrack(file.path().string().c_str());
		numtracks++;
	}
	if (trackNum == 0) {

	}
	//music.playMusicTrack(rand() % numtracks);
}


void music::functions::playThemeMusicTrack(int newTrack) {
	std::string menuDir = "";
	SDL2Music music;
	srand(time(NULL));

	std::string pathone = General::defaultFilepath + "\\sound\\music\\menu\\" + "Main Menu";
	std::string pathtwo = General::defaultFilepath + "\\sound\\music\\menu\\" + "Game Mode Select";
	std::string paththree = General::defaultFilepath + "\\sound\\music\\menu\\" + "Character Select";

	for (const auto& file : std::filesystem::directory_iterator(pathone)) {
		music.addChunk(file.path().string().c_str());
		music.addMusicTrack(file.path().string().c_str());
		break;
	}
	for (const auto& file : std::filesystem::directory_iterator(pathtwo)) {
		music.addChunk(file.path().string().c_str());
		music.addMusicTrack(file.path().string().c_str());
		break;
	}
	for (const auto& file : std::filesystem::directory_iterator(paththree)) {
		music.addChunk(file.path().string().c_str());
		music.addMusicTrack(file.path().string().c_str());
		break;
	}
	Mix_PlayChannel(3, music.getChunk(0), -1);
	Mix_PlayChannel(4, music.getChunk(1), -1);
	Mix_PlayChannel(5, music.getChunk(2), -1);
	Mix_Volume(4, 0);
	Mix_Volume(5, 0);
	//Mix_FadeOutChannel(1, 1000);
	//Mix_FadeInChannelTimed(2, 1000);
}
/*
void music::functions::PauseResumeMusicTrack() {
	SDL2Music music;
	music.Play_Pause();
}
*/