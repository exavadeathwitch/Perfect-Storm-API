#pragma once

#include "imgui/include/imgui.h"

#include "Core/Window/Window.hpp"


class Render : public modWindow
{
	public:
		Render() {
			modWindow();
		}
		Render(std::string name) {
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
		std::string layers[13] = { "SHADOW", "OPAQUE", "OPAQUE_BG_FAR", "TRANS_BG_FAR", "TRANS_BG_MID", "OPAQUE_PL", "OUTLINE", "TRANSPARENT", "TRANS_EFF", "BLUR", "ANM_BLUR", "SPRITE", "SPRITE_BG" };
		bool enablelayer[13] = { true, true, true, true, true, true, true, true, true, true, true, true, true };
		bool enableHud = true;
};