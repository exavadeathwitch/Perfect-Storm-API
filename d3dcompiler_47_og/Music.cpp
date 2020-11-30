#include <string>
#include "Music.h"
#include <iostream>
#include <filesystem>
#include "SDL2/SDL2Music.h"
#include "Stage.h"
using namespace std;
void Music::PlayStageMusicTrack()
{
	//Setup default filepath
	cout << "StageNumber when initializing: " << StageNumber << std::endl;
	string filepath;
	filepath = defaultmusicfilepath;
	cout << "Converting Int to String: " << StageNumber << endl;
	string stagenumber = to_string(StageNumber);
	filepath = defaultmusicfilepath + stagenumber + ".wav";
	char* filepath_arr;
	string str_obj(filepath);
	filepath_arr = &str_obj[0];
	cout << "filepath: " << filepath_arr << endl;
	SDL2Music music;
	if (filesystem::exists(filepath_arr) == 0)
	{
		return;
	}
	music.addMusicTrack(filepath_arr);
	music.playMusicTrack(0);
}