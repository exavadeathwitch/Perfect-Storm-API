#pragma once

#include <memory>

#include "Core/ModConsole/ModConsole.hpp"
#include "Core/Settings/Settings.hpp"
#include "Core/ModLoader/ModLoader.hpp"
#include "Util/Hook/HookManager.hpp"
#include "Util/Process/Process.hpp"
#include "imgui/include/imgui.h"
#include "Core/ModMenu/ModMenu.hpp"

namespace globals {
	static uintptr_t moduleBase = (uintptr_t)GetModuleHandle(NULL);
	inline ModLoader modLoader = ModLoader();
	inline ModMenu modMenu = ModMenu();
	inline std::unique_ptr<console::Console> modConsole = std::make_unique<console::Console>();
	inline settings::LoadedSettings settings = settings::LoadedSettings();
	inline std::unique_ptr<util::process::Process> process = std::make_unique<util::process::Process>("NSUNS4.exe");
	inline std::unique_ptr<util::hook::HookManager> hookManager = std::make_unique<util::hook::HookManager>();
}
