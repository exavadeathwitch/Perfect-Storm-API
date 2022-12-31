#pragma once

#include "imgui/include/imgui.h"

#include "Core/Window/Window.hpp"
inline bool start = false;
inline int gameSpeed = 1;
inline bool enableGameSpeed = false;
inline bool enableFrameStep = false;
inline int frameStepCount = 1;
inline bool frameStep = false;
inline int alternate = 1;
inline const char* speedSetting[] = { "0.5x", "1.0x", "2.0x", "3.0x" , "4.0x" };

class GameSpeed: public modWindow
{
	public:
		GameSpeed() {
			modWindow();
		}
		GameSpeed(std::string name) {
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
};