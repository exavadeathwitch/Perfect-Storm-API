#pragma once

#include "imgui/include/imgui.h"

#include "Core/Window/Window.hpp"

#include "Class/rostercoord.hpp"

#include "imguiwidget/widget.hpp"
class Roster : public modWindow
{
	public:
		Roster() {
			modWindow();
		}
		Roster(std::string name) {
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
		void modrostercoord(__int64 original, rostercoord newcoord);
		__int64 leftaddr = NULL;
		__int64 rightaddr = NULL;
		int side = 2;
		int rosterrunning = 0;
		rostercoord R1 = rostercoord();
		rostercoord R2 = rostercoord();
		float click = 1.0f;
		float ctrlclick = 5.0f;
};