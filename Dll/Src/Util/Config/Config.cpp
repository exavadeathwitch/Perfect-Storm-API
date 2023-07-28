#include "pch.hpp"
#include "Config.hpp"

#include <filesystem>

namespace Config {
	PluginConfig GetPluginsConfig(std::string pluginGUID) {
		// Check if the config/ directory exists
		if (!std::filesystem::exists("config/")) {
			std::filesystem::create_directory("config/");
		}
		
		// Check if the config/{pluginGUID}.cfg file exists
		if (!std::filesystem::exists("config/" + pluginGUID + ".cfg")) {
			// Return an empty config
			return { *(new toml::table()), pluginGUID };
		}

		// Load the config file
		toml::table config = toml::parse_file("config/" + pluginGUID + ".cfg");

		// Return the config
		return { config, pluginGUID };
	}

	void Save(PluginConfig& config) {
		// Save the config
		std::ofstream file("config/" + config.pluginGUID + ".cfg");
		file << config.config;
		file.close();
	}
}