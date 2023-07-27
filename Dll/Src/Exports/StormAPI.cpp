#include "StormAPI.h"

#include <Windows.h>

#include "../Util/Config/Config.hpp"
#include "../Util/Logging/Logger.h"

std::string GetPluginGUID() {
	HMODULE hModule = GetModuleHandle(NULL); // This way we can get the dll module handle which calls this function

	// TODO: Implement getting the dll's GUID
	// For now we'll just return the dlls name
	char path[MAX_PATH];
	GetModuleFileNameA(hModule, path, MAX_PATH);
	std::string pathStr = std::string(path);
	std::string name = pathStr.substr(pathStr.find_last_of("\\") + 1);

	// Remove the extension
	name = name.substr(0, name.find_last_of("."));

	return name;
}

std::string Storm_GetConfigString(std::string section, std::string key, std::string defaultValue) {
	Config::PluginConfig config = Config::GetPluginsConfig(GetPluginGUID());
	return Config::Bind<std::string>(config.config, section, key, defaultValue);
}

int Storm_GetConfigInt(std::string section, std::string key, int defaultValue) {
	Config::PluginConfig config = Config::GetPluginsConfig(GetPluginGUID());
	return Config::Bind<int>(config.config, section, key, defaultValue);
}

float Storm_GetConfigFloat(std::string section, std::string key, float defaultValue) {
	Config::PluginConfig config = Config::GetPluginsConfig(GetPluginGUID());
	return Config::Bind<float>(config.config, section, key, defaultValue);
}

bool Storm_GetConfigBool(std::string section, std::string key, bool defaultValue) {
	Config::PluginConfig config = Config::GetPluginsConfig(GetPluginGUID());
	return Config::Bind<bool>(config.config, section, key, defaultValue);
}

// Logging
void Storm_LogFatal(std::string message) {
	LOG_FATAL(GetPluginGUID(), message);
}

void Storm_LogError(std::string message) {
	LOG_ERROR(GetPluginGUID(), message);
}

void Storm_LogWarn(std::string message) {
	LOG_WARN(GetPluginGUID(), message);
}

void Storm_LogInfo(std::string message) {
	LOG_INFO(GetPluginGUID(), message);
}

void Storm_LogDebug(std::string message) {
	LOG_DEBUG(GetPluginGUID(), message);
}

void Storm_LogTrace(std::string message) {
	LOG_TRACE(GetPluginGUID(), message);
}
