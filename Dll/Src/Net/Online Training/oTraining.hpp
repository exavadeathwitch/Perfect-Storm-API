#pragma once

#include "pch.hpp"

namespace OTraining {
	inline bool trainingisOn = 1;
	inline const char* SGitems[]{ "Normal", "Stay at 0", "Max" };
	inline int selectedSGItem = 0;
	inline const char* Litems[]{ "Normal", "Unlimited", "Awakening" };
	inline int selectedLItem = 0;
	inline bool tcheckBox[5] = { false, false, false, false, false };
	class functions {
	public:
		static void enableOnlineTraining ();
	};
}