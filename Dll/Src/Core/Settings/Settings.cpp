#include "pch.hpp"

#include "Settings.hpp"

#include "json/single_include/json.hpp"

#include "Util/Util.hpp"

#include "Core/Globals.hpp"
namespace settings {
	void updateSettings() {
		globals::settings.m_Language = globals::modMenu.langarr[globals::modMenu.langindex];
		globals::settings.m_ConvertMenuMessages = globals::modMenu.convertmenumessages;
		globals::settings.m_ShouldEnableConsole = globals::modMenu.ec;
		globals::settings.m_MaxModsPerColumn = globals::modMenu.maxMods;

	}
	void onStartup() noexcept {
		const auto modPath = util::getModPath();

		if (!std::filesystem::exists(modPath)) {
			std::filesystem::create_directory(modPath);

			applyDefaults();
		}
		else {
			load();
		}
	}

	void applyDefaults() noexcept {
		std::ofstream fileOut(util::getSettingsPath());

		nlohmann::json settings;

		settings["General"]["Console"] = true;
		settings["General"]["Language"] = "English";
		settings["General"]["MaxModsPerColumn"] = 6;
		settings["General"]["ConvertMenuMessages"] = false;

		fileOut << settings.dump(1);
	}

	void save() noexcept {
		std::ofstream fileOut(util::getSettingsPath(), std::ios::trunc);

		nlohmann::json settings;

		settings["General"]["Console"] = globals::settings.m_ShouldEnableConsole;
		settings["General"]["Language"] = globals::settings.m_Language;
		settings["General"]["MaxModsPerColumn"] = globals::settings.m_MaxModsPerColumn;
		settings["General"]["ConvertMenuMessages"] = globals::settings.m_ConvertMenuMessages;

		fileOut << settings.dump(1);
	}

	void load() noexcept {
		std::ifstream fileIn(util::getSettingsPath());

		const std::string buffer{std::istreambuf_iterator<char>(fileIn), std::istreambuf_iterator<char>()};

		fileIn.close();

		auto parsedJson = nlohmann::json::parse(buffer);

		globals::settings.m_ShouldEnableConsole = parsedJson["General"]["Console"].get<bool>();
		globals::settings.m_Language = parsedJson["General"]["Language"].get<std::string>();
		globals::settings.m_MaxModsPerColumn = parsedJson["General"]["MaxModsPerColumn"].get<int>();
		globals::settings.m_ConvertMenuMessages = parsedJson["General"]["ConvertMenuMessages"].get<bool>();
	}
}