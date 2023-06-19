#include "pch.hpp"

#include "Util/Sound/SDL2Music.h"
#include "Util/Sound/SDLInit.h"
#include <sdl2/include/SDL.h>
int musicVol = 16;

SDL2Music::SDL2Music()
{
	SDLInit::initSDLSound();
}

void SDL2Music::addMusicTrack(const char* path)
{
	Mix_Music* tmp_music = Mix_LoadMUS(path);

	if (tmp_music != nullptr)
	{
		mMusics.push_back(tmp_music);
	}
	else
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't load audio: %s",
			Mix_GetError());
	}
}

void SDL2Music::addChunk(const char* path)
{
	Mix_Chunk* tmp_chunk = Mix_LoadWAV(path);

	if (tmp_chunk != nullptr)
	{
		mChunks.push_back(tmp_chunk);
	}
	else
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't load audio: %s",
			Mix_GetError());
	}
}

Mix_Chunk* SDL2Music::getChunk(const int which)
{
	return mChunks.at(which);
}

void SDL2Music::playMusicTrack(const int which)
{
	//Mix_VolumeMusic(musicVol);
	if (which > mMusics.size())
	{
		return;
	}
	Mix_PlayMusic(mMusics.at(which), -1);
	m_Playing = true;
}

void SDL2Music::playChannelTrack(const int which, unsigned int channel)
{
	//Mix_VolumeMusic(musicVol);
	if (which > mChunks.size())
	{
		return;
	}
	Mix_PlayChannel(channel, mChunks.at(which), -1);
}

void SDL2Music::volume_Channel(unsigned int channel, int volume) {
	Mix_Volume(channel, volume);
}

void SDL2Music::Play_Pause()
{
	if (m_Playing && !m_Paused)
	{
		Mix_PauseMusic();
		m_Paused = true;
	}
	else if (m_Playing && m_Paused)
	{
		Mix_ResumeMusic();
		m_Paused = false;
	}
	else
	{
		return;
	}
}

void SDL2Music::volume_Music()
{
	Mix_VolumeMusic(1);
}

void SDL2Music::Halt_Music()
{
	Mix_HaltMusic();
}

int SDL2Music::Playing_Music()
{
	return Mix_PlayingMusic();
}

void SDL2Music::Fade_Out(int ms)
{
	Mix_FadeOutMusic(ms);
}