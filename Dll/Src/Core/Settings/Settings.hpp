#pragma once

namespace settings {
	struct LoadedSettings {
		bool m_ShouldEnableConsole{};
		std::string m_Version{};
		int m_ShouldAutoUpdate{};
	};

	void onStartup() noexcept;
	void applyDefaults() noexcept;
	void save() noexcept;
	void load() noexcept;
}
