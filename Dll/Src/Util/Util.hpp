#pragma once

#include <filesystem>

namespace util {
	static std::filesystem::path getModPath() noexcept {
		return std::filesystem::current_path() / "PSAPI";
	}

	static std::filesystem::path getSettingsPath() noexcept {
		return getModPath() / "config.json";
	}
}
