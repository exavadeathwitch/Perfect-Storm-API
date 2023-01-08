#include "pch.hpp"

#include "Settings.hpp"

#include "json/single_include/json.hpp"

#include "Util/Util.hpp"

#include "Core/DebugMenu/DebugMenu.hpp"

#include "Util/Console/Console.hpp"
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
		settings["autoboot"] = 0;
		settings["autounlockallchars"] = true;
		settings["debugConsole"] = true;
		settings["debugGameplay"] = true;
		settings["displayloadXFBIN"] = false;
		settings["enableKeyboard"] = false;
		settings["language"] = "English";
		settings["R3framestep"] = false;

		fileOut << settings.dump(1);
	}

	void save() noexcept {
		std::ofstream fileOut(util::getSettingsPath(), std::ios::trunc);

		nlohmann::json settings;


		settings["autoboot"] = c.autoboot;
		settings["autounlockallchars"] = c.autounlockallchars;
		settings["debugConsole"] = sdk::game::debugPrint;
		settings["debugGameplay"] = c.debugGameplay;
		settings["displayloadXFBIN"] = c.displayloadXFBIN;
		settings["enableKeyboard"] = c.enableKeyboard;
		settings["language"] = c.langarr[c.lang];
		settings["R3framestep"] = c.R3framestep;

		fileOut << settings.dump(1);
	}

	void load() noexcept {
		std::ifstream fileIn(util::getSettingsPath());
		const std::string buffer{std::istreambuf_iterator<char>(fileIn), std::istreambuf_iterator<char>()};
		
		auto parsedJson = nlohmann::json::parse(buffer);
		c.autoboot = parsedJson["autoboot"].get<int>();
		c.autounlockallchars = parsedJson["autounlockallchars"].get<bool>();
		sdk::game::debugPrint = parsedJson["debugConsole"].get<bool>();
		c.debugGameplay = parsedJson["debugGameplay"].get<bool>();
		c.displayloadXFBIN = parsedJson["displayloadXFBIN"].get<bool>();
		c.enableKeyboard = parsedJson["enableKeyboard"].get<bool>();
		c.R3framestep = parsedJson["R3framestep"].get<bool>();
		std::string lang = parsedJson["language"].get<std::string>();
		for (int x = 0; x < 13; x++) {
			if (lang == c.langarr[x]) {
				c.lang = x;
				break;
			}
		}
		fileIn.close();
	}
}