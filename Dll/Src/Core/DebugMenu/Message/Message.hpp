#pragma once

#include "imgui/include/imgui.h"

#include "Core/Window/Window.hpp"


class Message : public modWindow
{
	public:
		Message() {
			modWindow();
		}
		Message(std::string name) {
			this->name = name;
		}
		void createMenu() {
			if (!this->enableMenu)
				return;
			ImGui::Begin(this->name.c_str(), &this->enableMenu);
			this->runMenu();
			ImGui::End();
		}
		void runMenu();
		char buffer[550];
		bool showTranslatedGameMessages = true;
		bool showMenuGameMessages = true;
};