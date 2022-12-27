#pragma once
#include "pch.hpp"

#include "imgui/include/imgui.h"

class modWindow
{
	public:
		modWindow() {
			this->name = "";
		}
		modWindow(std::string name) {
			this->name = name;
		}
		void createMenu() {
			if (!this->enableMenu)
				return;
			ImGui::Begin(this->name.c_str(), NULL);
			this->runMenu();
			ImGui::End();
		}
		void toggleMenu() {
			if (enableMenu == false)
				enableMenu = true;
			else
				enableMenu = false;
		}
		void runMenu() {};
		std::string name = "";
		bool enableMenu = false;
};