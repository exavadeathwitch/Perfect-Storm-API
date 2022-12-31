#pragma once

#include "imgui/include/imgui.h"

#include "Core/Window/Window.hpp"


class Config : public modWindow
{
	public:
		Config() {
			modWindow();
		}
		Config(std::string name) {
			this->name = name;
		}
		void createMenu() {
			if (!this->enableMenu)
				return;
			ImGui::Begin(this->name.c_str(), NULL);
			this->runMenu();
			ImGui::End();
		}
		void runMenu();
		int autoboot = 0;
		bool autounlockallchars = true;
		bool debugGameplay = true;
		bool displayloadXFBIN = false;
		bool enableKeyboard = false;
		bool R3framestep = false;
		int lang = 0;
		std::string langarr[13] = { "English", "French", "Italian", "German", "Spanish", "Arabic", "Polish", "Russian", "Japanese", "Portuguese", "Thai", "Korean", "Chinese(Traditional)" };
};