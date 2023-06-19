#include "pch.hpp"

#include "Util/Sound/SDLInit.h"
#include "sdl2/include/SDL_mixer.h"
#include "sdl2/include/SDL.h"

static SDLInit* sdlsound = nullptr;

void SDLInit::initSDLSound()
{
	if (sdlsound)
	{
		return;
	}

	sdlsound = new SDLInit();
}
SDLInit::SDLInit()
{
	// init sound
	SDL_Init(SDL_INIT_AUDIO);
	
	int audio_rate = 41000;
	Uint16 audio_format = AUDIO_S16;
	int audio_channels = 2;
	int audio_buffers = 0;
	if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, 4096) != 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't init audio: %s", Mix_GetError());
		exit(-1);
	}
	else
	{
		m_SoundInitialized = true;
	}
	std::cout << Mix_AllocateChannels(4);
}
