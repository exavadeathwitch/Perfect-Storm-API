#pragma once

#include <filesystem>

namespace util {
	static std::filesystem::path getModPath() noexcept {
		return std::filesystem::current_path() / "PSEngine";
	}

	static std::filesystem::path getSettingsPath() noexcept {
		return getModPath() / "config.json";
	}
}
