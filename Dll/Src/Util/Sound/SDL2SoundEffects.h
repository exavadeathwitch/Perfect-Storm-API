#pragma once

#include "pch.hpp"
#include "sdl2/include/SDL_mixer.h"
#include <vector>
class SDL2SoundEffects
{
public:
	SDL2SoundEffects();

	void addSoundEffect(const char* path);

	void playSoundEffect(const int which) const;

	void volume_SoundEffects();
private:
	std::vector<Mix_Chunk*> mSoundEffectBank;
};

