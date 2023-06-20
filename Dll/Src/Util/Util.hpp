#pragma once

#include <filesystem>

namespace util {
	static std::filesystem::path getModPath() noexcept {
		return std::filesystem::current_path() / "stormapi";
	}

	static std::filesystem::path getSettingsPath() noexcept {
		return getModPath() / "settings.json";
	}
}
