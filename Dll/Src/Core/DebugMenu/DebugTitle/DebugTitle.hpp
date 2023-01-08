#pragma once

#include "imgui/include/imgui.h"

#include "texture/texture.hpp"
inline bool runTitle = true;
inline bool bootFB = false;
inline bool skipOpening = false;

class DebugTitle
{
	public:
		static void runDebugTitle();
		static void loadBackground();
};