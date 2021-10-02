#include "pch.hpp"

#include "Settings.hpp"

#include "json/single_include/json.hpp"

#include "Util/Util.hpp"

namespace settings {
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
		settings["General"]["Version"] = "Default";
		settings["General"]["Auto-Update"] = true;
		settings["General"]["Frame Delay Position"] = 0;
		settings["General"]["Enable Online Training"] = false;
		settings["General"]["Custom Menu Music"] = false;
		fileOut << settings.dump(1);
	}

	void save() noexcept {
		std::ofstream fileOut(util::getSettingsPath(), std::ios::trunc);

		nlohmann::json settings;

		settings["General"]["Console"] = globals::settings->m_ShouldEnableConsole;
		settings["General"]["Version"] = globals::settings->m_Version;
		settings["General"]["Auto-Update"] = globals::settings->m_ShouldAutoUpdate;
		settings["General"]["Frame Delay Position"] = globals::settings->m_frameDelayPosition;
		settings["General"]["Enable Online Training"] = globals::settings->m_enableTraining;
		settings["General"]["Custom Menu Music"] = globals::settings->m_customMusicToggle;
		fileOut << settings.dump(1);
	}

	void load() noexcept {
		std::ifstream fileIn(util::getSettingsPath());

		const std::string buffer{std::istreambuf_iterator<char>(fileIn), std::istreambuf_iterator<char>()};

		fileIn.close();

		auto parsedJson = nlohmann::json::parse(buffer);

		globals::settings->m_ShouldEnableConsole = parsedJson["General"]["Console"].get<bool>();
		globals::settings->m_Version = parsedJson["General"]["Version"].get<std::string>();
		globals::settings->m_ShouldAutoUpdate = parsedJson["General"]["Auto-Update"].get<bool>();
		globals::settings->m_frameDelayPosition = parsedJson["General"]["Frame Delay Position"].get<int>();
		globals::settings->m_enableTraining = parsedJson["General"]["Enable Online Training"].get<bool>();
		globals::settings->m_customMusicToggle = parsedJson["General"]["Custom Menu Music"].get<bool>();
	}
}