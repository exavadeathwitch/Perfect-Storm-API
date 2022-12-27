#pragma once

#include "imgui/include/imgui.h"

#include "GameSpeed/GameSpeed.hpp"

inline bool enableDebugMenu = false;

inline GameSpeed gs = GameSpeed("Game Speed");
class DebugMenu
{
	public:
		static void runDebugMenu();
};