#include "pch.hpp"

#include "Music.hpp"

#include "SDL2Music.h"

#include "General/general.hpp"

#include "GameSettings/gameSettings.hpp"

#include "Stage/Stage.hpp"

#include <string>

#include <filesystem>

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
	std::cout << gameSettings::musicVol << std::endl;
	std::cout << gameSettings::musicVol / 1.25 << std::endl;
	music.playMusicTrack(rand() % numtracks);
}

void music::functions::playStageMusicTrack() {
	SDL2Music music;
	std::string dirpath = General::defaultFilepath + "\\sound\\music\\stage\\" + Stage::stageName;
	std::string str_obj(dirpath);
	char* dirpath_arr = &str_obj[0];

	srand(time(NULL));

	int numtracks = 0;
	for (const auto& file : std::filesystem::directory_iterator(dirpath)) {
		
		music.addMusicTrack(file.path().string().c_str());
		numtracks++;
	}
	music.playMusicTrack(rand() % numtracks);
}
/*
void music::functions::PauseResumeMusicTrack() {
	SDL2Music music;
	music.Play_Pause();
}
*/