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