#pragma once

#include "pch.hpp"
class SDLInit
{
public:
	static void initSDLSound();

	SDLInit();
	~SDLInit();

private:
	bool m_SoundInitialized = false;
};

