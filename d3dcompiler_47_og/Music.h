#ifndef MUSIC_H 
#define MUSIC_H

#include <Windows.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string>

static std::string defaultmusicfilepath = "";//".\\PerfectStorm\\";
static int tracknumber;

namespace moddingApi
{

	class Music
	{
	public:
		static void PlayStageMusicTrack();
		static void PlayMusicTrackTest();
		static void PauseResumeMusicTrack();
	};
}
#endif