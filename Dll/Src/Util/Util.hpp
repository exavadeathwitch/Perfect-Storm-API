#pragma once

#include <filesystem>

namespace util {
	std::filesystem::path getModPath() noexcept {
		return std::filesystem::current_path() / "Perfect Storm";
	}

	std::filesystem::path getSettingsPath() noexcept {
		return getModPath() / "settings.json";
	}

	bool endsWith(const std::string& mainStr, const std::string& toMatch) {
		if (mainStr.size() >= toMatch.size() &&
			mainStr.compare(mainStr.size() - toMatch.size(), toMatch.size(), toMatch) == 0)
			return true;
		else
			return false;
	}
}
