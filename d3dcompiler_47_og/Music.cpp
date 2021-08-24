#include <string>
#include "Music.h"
#include <iostream>
#include <filesystem>
#include "SDL2/SDL2Music.h"
#include "Stage.h"

using namespace std;
void moddingApi::Music::PlayStageMusicTrack()
{
	SDL2Music music;
	//Setup default filepath
	int StageNumber = 1;
	cout << "StageNumber when initializing: " << StageNumber << std::endl;
	string filepath;
	filepath = defaultmusicfilepath;
	cout << "Converting Int to String: " << StageNumber << endl;
	string stagenumber = to_string(StageNumber);
	int trackNum = rand() % 4 + 1;
	switch (trackNum) {
	case 1: Mix_VolumeMusic(128);
		break;
	default: Mix_VolumeMusic(0);
		break;
	}

	filepath = defaultmusicfilepath + stageName + "\\Track" + to_string(trackNum) + ".wav";
	string filepathDefault = defaultmusicfilepath + stageName + "\\Track1.wav";
	char* filepath_arr;
	char* deffilepath_arr;
	string str_obj(filepath);
	string defstr_obj(filepathDefault);
	filepath_arr = &str_obj[0];
	deffilepath_arr = &defstr_obj[0];
	cout << "filepath: " << filepath_arr << endl;
	if (filesystem::exists(filepath_arr) == 0)
	{
		std::cout << "blabla" << std::endl;
	}
	else
	{
		music.addMusicTrack(filepath_arr);
		music.playMusicTrack(0);
		return;
	}
	if (filesystem::exists(deffilepath_arr) == 1)
	{
		music.addMusicTrack(deffilepath_arr);
		music.playMusicTrack(0);
		return;
	}
}

void moddingApi::Music::PlayMusicTrackTest() {
	SDL2Music music;
	string filepath = "test.wav";
	string str_obj(filepath);
	char* filepath_arr = &str_obj[0];
	music.addMusicTrack(filepath_arr);
	music.playMusicTrack(0);
}

void moddingApi::Music::PauseResumeMusicTrack() {
	SDL2Music music;
	music.Play_Pause();
}