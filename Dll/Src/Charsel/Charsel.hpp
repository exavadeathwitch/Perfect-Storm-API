#pragma once

namespace Charsel {
	std::vector<DWORD>bannedPresets;
	class functions {
	public:
		static int __fastcall accessPreset(__int64 a1, int a2, int a3, __int64 a4);
		static void filterPresetID(DWORD preset1, DWORD preset2, DWORD preset3);
		static void initializeBannedPresetList();
	};
}