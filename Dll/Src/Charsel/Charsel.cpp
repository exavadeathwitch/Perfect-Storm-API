#include "pch.hpp"

#include "Charsel.hpp"

#include <vector>

int __fastcall Charsel::functions::accessPreset(__int64 a1, int a2, int a3, __int64 a4) {
	int retval = globals::hookManager->getOriginal<decltype(&Charsel::functions::accessPreset)>(Charsel::functions::accessPreset)(a1, a2, a3, a4);
	Charsel::functions::filterPresetID(*(DWORD*)(a4), *(DWORD*)(a4 + 0xC), * (DWORD*)(a4 + 0x18));
	return retval;
}

void Charsel::functions::initializeBannedPresetList() {
	Charsel::bannedPresets.push_back(1);
}


void Charsel::functions::filterPresetID(DWORD preset1, DWORD preset2, DWORD preset3) {
	if ((preset1 && preset2 && preset3) == 0)
		return;
	for (auto i = Charsel::bannedPresets.begin(); i != Charsel::bannedPresets.size(); ++i)

}