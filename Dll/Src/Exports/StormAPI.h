#pragma once

#define STORMAPI __declspec(dllexport)

#include <string>

// Config
STORMAPI std::string Storm_GetConfigString(std::string section, std::string key, std::string defaultValue);
STORMAPI int Storm_GetConfigInt(std::string section, std::string key, int defaultValue);
STORMAPI float Storm_GetConfigFloat(std::string section, std::string key, float defaultValue);
STORMAPI bool Storm_GetConfigBool(std::string section, std::string key, bool defaultValue);

// Logging
STORMAPI void Storm_LogFatal(std::string message);
STORMAPI void Storm_LogError(std::string message);
STORMAPI void Storm_LogWarn(std::string message);
STORMAPI void Storm_LogInfo(std::string message);
STORMAPI void Storm_LogDebug(std::string message);
STORMAPI void Storm_LogTrace(std::string message);
