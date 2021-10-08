#pragma once
#include <sdl2/include/SDL_mixer.h>
#include <vector>
#include "pch.hpp"
class SDL2Music
{
public:
	SDL2Music();

	int Playing_Music();

	void addMusicTrack(const char* path);

	void playMusicTrack(const int which);

	void Play_Pause();

	void Halt_Music();

	void volume_Music();

	void Fade_Out(int ms);

private:

	std::vector<Mix_Music*> mMusics;

	bool m_Paused = false;

	bool m_Playing = false;
};

