#pragma once

#include <memory>

#include "Core/ModConsole/ModConsole.hpp"
#include "Core/Settings/Settings.hpp"

#include "Util/Hook/HookManager.hpp"
#include "Util/Process/Process.hpp"

namespace globals {
	inline std::unique_ptr<console::Console> modConsole = std::make_unique<console::Console>();
	inline std::unique_ptr<settings::LoadedSettings> settings = std::make_unique<settings::LoadedSettings>();
	inline std::unique_ptr<util::process::Process> process = std::make_unique<util::process::Process>("NSUNS4.exe");
	inline std::unique_ptr<util::hook::HookManager> hookManager = std::make_unique<util::hook::HookManager>();
}
