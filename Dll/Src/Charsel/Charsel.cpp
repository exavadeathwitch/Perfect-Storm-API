#include "pch.hpp"

#include "Charsel.hpp"

#include <vector>

int __fastcall Charsel::functions::accessPreset(__int64 a1, int a2, int a3, __int64 a4) {
	int retval = globals::hookManager->getOriginal<decltype(&Charsel::functions::accessPreset)>(Charsel::functions::accessPreset)(a1, a2, a3, a4);
	//Charsel::functions::filterPresetID(a4);
	return retval;
}

//This function initializes preset ids that we do not want to be accessible through character select presets i.e. story mode characters.
//We will also use this to remove costumes of dlc characters from the preset selection.
void Charsel::functions::initializeBannedPresetList() {
	Charsel::bannedPresets.push_back(1);
}

/*
void Charsel::functions::filterPresetID(__int64 basePresetAddr) {
	preset1 = DWORD(a4)
	preset2 = DWORD(a4)
	preset3 = DWORD(a4)
	if (preset1 == 0 && preset2 == 0 && preset3 == 0)
		return;

	for (auto i = Charsel::bannedPresets.begin(); i != Charsel::bannedPresets.size(); ++i)

}*/


