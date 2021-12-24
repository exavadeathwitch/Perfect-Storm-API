#include "pch.hpp"

#include "gameSettings.hpp"

#include "Util/Sound/SDL2Music.h"

#include "Core/Hooks/Hooks.hpp"

#include "Player/Mechanics/mech.hpp"

void gameSettings::functions::updateSettings() {
	gameSettings::xRes = *(DWORD*)(globals::moduleBase + 0x1561108);
	gameSettings::yRes = *(DWORD*)(globals::moduleBase + 0x156110C);
	gameSettings::musicVol = *(BYTE*)(globals::moduleBase + 0x161FEEA);
	gameSettings::fps = *(BYTE*)(globals::moduleBase + 0x1561138);
}

int __fastcall gameSettings::functions::newSettings(__int64 a1) {
	const auto retval = globals::hookManager->getOriginal<decltype(&gameSettings::functions::newSettings)>(gameSettings::functions::newSettings)(a1);
	gameSettings::functions::updateSettings();
	SDL2Music music;
	Mix_VolumeMusic(gameSettings::musicVol/1.25);
	return retval;
}

__int64 __fastcall gameSettings::functions::updateResSettings(__int64 a1) {
	const auto retval = globals::hookManager->getOriginal<decltype(&gameSettings::functions::updateResSettings)>(gameSettings::functions::updateResSettings)(a1);
	//mechanics::imguiOn = 0;
	return retval;
}