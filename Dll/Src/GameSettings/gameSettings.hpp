#pragma once

#include "Util/Memory/Modify.hpp"

namespace gameSettings {
	//In-game settings
	inline DWORD xRes = *(DWORD*)(globals::moduleBase + 0x1561108);
	inline DWORD yRes = *(DWORD*)(globals::moduleBase + 0x156110C);
	inline BYTE musicVol = *(BYTE*)(globals::moduleBase + 0x161FEEA);
	inline BYTE fps = *(BYTE*)(globals::moduleBase + 0x1561138);
	class functions {
	public:
		static void updateSettings();
		static int newSettings(__int64 a1);
	};
}