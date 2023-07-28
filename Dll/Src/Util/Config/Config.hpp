#pragma once

#include "toml.hpp"

namespace Config {
	struct PluginConfig {
		toml::table& config;
		std::string pluginGUID;
	};

	PluginConfig GetPluginsConfig(std::string pluginGUID);
	void Save(PluginConfig& config);

	template<typename T>
	inline std::optional<T> Bind(toml::table& config, std::string section, std::string key, T defaultValue) {
		// Check if the key exists
		//if (!config[section][key].is<T>()) {
			// Set the default value
		//	config.insert_or_assign(section, toml::table{ { key, defaultValue } });
		//}

		// Return the value
		//return config[section][key].value<T>();

		return std::optional<T>();
	}

	template<typename T>
	inline void Set(toml::table& config, std::string section, std::string key, T value) {
		// Check if the section exists
		if (!config.contains(section)) {
			// Create the section
			config[section] = toml::table();
		}

		// Set the value
		config[section][key] = value;
	}
}