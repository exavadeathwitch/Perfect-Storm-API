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

		fileOut << settings.dump(1);
	}

	void save() noexcept {
		std::ofstream fileOut(util::getSettingsPath(), std::ios::trunc);

		nlohmann::json settings;

		settings["General"]["Console"] = globals::settings->m_ShouldEnableConsole;

		fileOut << settings.dump(1);
	}

	void load() noexcept {
		std::ifstream fileIn(util::getSettingsPath());

		const std::string buffer{std::istreambuf_iterator<char>(fileIn), std::istreambuf_iterator<char>()};

		fileIn.close();

		auto parsedJson = nlohmann::json::parse(buffer);

		globals::settings->m_ShouldEnableConsole = parsedJson["General"]["Console"].get<bool>();
	}
}