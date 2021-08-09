#pragma once

#include <filesystem>

namespace util {
	std::filesystem::path getModPath() noexcept {
		return std::filesystem::current_path() / "Perfect Storm";
	}

	std::filesystem::path getSettingsPath() noexcept {
		return getModPath() / "settings.json";
	}
}
