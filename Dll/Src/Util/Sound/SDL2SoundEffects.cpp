#include "pch.hpp"


#include "Util/Sound/SDL2SoundEffects.h"
#include "sdl2/include/SDL.h"
#include <iostream>
#include "Util/Sound/SDLInit.h"


SDL2SoundEffects::SDL2SoundEffects()
{
	SDLInit::initSDLSound();
}


void SDL2SoundEffects::addSoundEffect(const char* path)
{
	Mix_Chunk* tmpChunk = Mix_LoadWAV(path);

	if (tmpChunk != nullptr)
	{
		mSoundEffectBank.push_back(tmpChunk);
		std::cout << (mSoundEffectBank.size() - 1) << " Sound is ready, path: " << path << '\n';
	}
	else
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't init audio: %s", Mix_GetError());
	}
}

void SDL2SoundEffects::playSoundEffect(const int which) const
{
	if (which > mSoundEffectBank.size() - 1)
	{
		std::cout << "Sound out of range.\n";
		return;
	}
	Mix_PlayChannel(-1, mSoundEffectBank[which], 0);

	std::cout << "Played Sound: " << which << '\n';
}
void SDL2SoundEffects::volume_SoundEffects()
{
	Mix_Volume(-1, 128);
}