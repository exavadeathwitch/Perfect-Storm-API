#pragma once

#include "imgui/include/imgui.h"

#include "GameSpeed/GameSpeed.hpp"

#include "Config/Config.hpp"

#include "Render/Render.hpp"

#include "Core/DebugMenu/DebugTitle/DebugTitle.hpp"

#include "Core/DebugMenu/Roster/Roster.hpp"
inline bool enableDebugMenu = false;

inline GameSpeed gs = GameSpeed("Game Speed");
inline Config c = Config("Config");
inline Render r = Render("Render");
inline Roster ro = Roster("Roster Coordinates");
class DebugMenu
{
public:
	static void runDebugMenu();
	static void saveConfig();
};