#pragma once

#include "../Util/Config/toml.hpp"

namespace Config {
	struct PluginConfig {
		toml::table& config;
		std::string pluginGUID;
	};

	PluginConfig GetPluginsConfig(std::string pluginGUID);
	
	template<typename T>
	inline T Bind(toml::table& config, std::string section, std::string key, T defaultValue) {
		// Check if the section exists
		if (!config.contains(section)) {
			// Create the section
			config[section] = toml::table();
		}

		// Check if the key exists
		if (!config[section].contains(key)) {
			// Create the key
			config[section][key] = defaultValue;
		}

		// Return the value
		return config[section][key].value<T>();
	}

	void Save(PluginConfig& config);
}