#include "pch.hpp"

#include "ModConsole.hpp"

#include "imgui/include/imgui.h"

namespace console {
	void Console::render() noexcept {
		if (!m_ShouldRender)
			return;
		showConsole(NULL);
		return;
		if (ImGui::Begin("Perfect Storm Console", &m_ShouldRender, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse)) {
			ImGui::SetCursorPosY(ImGui::GetWindowHeight() - 25.f);

			std::string command;
			command.resize(50);
			ImGui::InputText("##commandInput", &command[0], sizeof(command));

			command = command.substr(0, command.find('\0'));

			ImGui::SameLine();

			if (ImGui::Button("send") || (GetAsyncKeyState(VK_RETURN) & 1)) {
				if (command[0]) {
					m_Messages.emplace_back(command);

					if (m_Commands.find(command) != m_Commands.end())
						runCommand(command);
					else
						m_Messages.emplace_back(std::format("\"{}\" is not a valid command!\n", command));
				}
			}

			ImGui::SetCursorPosY(ImGui::GetWindowHeight() - ImGui::GetWindowHeight() + 20.f);

			if (!m_Messages.empty())
				for (const std::string_view current : m_Messages)
					ImGui::Text(current.data());

			command.clear();

		}ImGui::End();
	}

	void Console::buildCommands() noexcept {
		addCommand({.m_Name = "help", .m_Description = "Displays this message", .m_Action
				   = [&, this]() -> void {
			for (const auto& current : m_Commands | std::views::values)
				m_Messages.emplace_back(std::format("{} - {}\n", current.m_Name, current.m_Description));
		}});

		addCommand({.m_Name = "clear", .m_Description = "Clears the console", .m_Action
				   = [&, this]() -> void {
			m_Messages.clear();
		}});
	}

	void Console::addCommand(const Command& command) noexcept {
		m_Commands[command.m_Name] = {.m_Name = command.m_Name, .m_Description = command.m_Description, .m_Action = command.m_Action};
	}

	void Console::runCommand(const std::string_view name) noexcept {
		m_Commands[name].m_Action();
	}

	void Console::changeRender() {
		if (this->m_ShouldRender == true)
			this->m_ShouldRender = false;
		else
			this->m_ShouldRender = true;
	}
}