#pragma once

#include <functional>

namespace console {
	inline bool enabled = 0;
	class Console {
	public:
		struct Command {
			std::string_view m_Name;
			std::string_view m_Description;
			std::function<void()> m_Action;
		};
	public:
		bool render() noexcept;
		void buildCommands() noexcept;
		void addCommand(const Command& command) noexcept;
		void runCommand(std::string_view name) noexcept;
	private:
		bool m_ShouldRender = true;
		std::vector<std::string> m_Messages;
		std::unordered_map<std::string_view, Command> m_Commands;
	};
}
