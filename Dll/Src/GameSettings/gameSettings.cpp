#include "pch.hpp"

#include "gameSettings.hpp"

void gameSettings::functions::updateSettings() {
	gameSettings::xRes = *(DWORD*)(globals::moduleBase + 0x1561108);
	gameSettings::yRes = *(DWORD*)(globals::moduleBase + 0x156110C);
	gameSettings::musicVol = *(BYTE*)(globals::moduleBase + 0x161FEEA);
	gameSettings::fps = *(BYTE*)(globals::moduleBase + 0x1561138);
}