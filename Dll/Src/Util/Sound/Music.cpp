#include "pch.hpp"

#include "Music.hpp"

#include "SDL2Music.h"

#include "General/general.hpp"

#include <string>

#include <filesystem>

#include <time.h>

void music::functions::playMusicTrackTest() {
	SDL2Music music;
	std::string dirpath = General::defaultFilepath + "\\sound\\music\\stage";
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
void music::functions::playStageMusicTrack() {

	SDL2Music music;
	//Setup default filepath
	int StageNumber = 1;
	std::string filepath = General::defaultFilepath + "\\sound\\music\\stage";
	
	std::string stagenumber = std::to_string(StageNumber);
	int trackNum = rand() % 4 + 1;

	filepath = filepath + stageName + "\\Track" + std::to_string(trackNum) + ".wav";
	std::string filepathDefault = General::defaultFilepath + "\\sound\\music\\stage" + stageName + "\\Track1.wav";
	char* filepath_arr;
	char* deffilepath_arr;
	std::string str_obj(filepath);
	std::string defstr_obj(filepathDefault);
	filepath_arr = &str_obj[0];
	deffilepath_arr = &defstr_obj[0];
	if (std::filesystem::exists(filepath_arr) == 0)
	{

	}
	else
	{
		music.addMusicTrack(filepath_arr);
		music.playMusicTrack(0);
		return;
	}
	if (std::filesystem::exists(deffilepath_arr) == 1)
	{
		music.addMusicTrack(deffilepath_arr);
		music.playMusicTrack(0);
		return;
	}
	
}

void music::functions::PauseResumeMusicTrack() {
	SDL2Music music;
	music.Play_Pause();
}
*/