#pragma once

namespace settings {
	struct LoadedSettings {
		bool m_ShouldEnableConsole{};
		bool m_ConvertMenuMessages{};
		std::string m_Language{};
		int m_MaxModsPerColumn{};
		std::string m_Version{};
		bool m_ShouldAutoUpdate{};
	};

	void onStartup() noexcept;
	void applyDefaults() noexcept;
	void save() noexcept;
	void load() noexcept;
	void updateSettings();
}