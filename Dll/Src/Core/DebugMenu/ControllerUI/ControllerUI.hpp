#pragma once

#include "pch.hpp"

#include "Core/DebugMenu/DebugMenu.hpp"

#include "Core/Window/Window.hpp"

#include "Class/controllertexture.hpp"

#include "Class/gamepad.hpp"

#include "texture/texture.hpp"

#include "Game/cc/ccGame/ccGame.hpp"

class controllerUI : public modWindow
{
public:
	controllerUI() {
		modWindow();
	}
	controllerUI(std::string name) {
		this->name = name;
	}
	void loadTextures();
	void createMenu() {
		if (!this->enableMenu)
			return;
		ImGui::Begin(this->name.c_str(), &this->enableMenu);
		this->runMenu();
		ImGui::End();
	}
	pad getPad(int index) {
		return sysPads[index];
	}
	void padMenu() {
		this->grabInputs();
		for (int x = 0; x < sizeof(this->enablesysPads); x++) {
			if (this->enablesysPads[x])
				controllerUI::createsysPadWindow(("Pad " + std::to_string(x)).c_str(), this->sysPads[x], x, &this->enablesysPads[x], &this->adjustsysPads[x]);
		}
		for (int x = 0; x < sizeof(this->enableduelPads); x++) {
			if (this->enableduelPads[x])
				this->createduelPadWindow((std::to_string(x) + "duel").c_str(), x, &this->enableduelPads[x], &this->adjustduelPads[x]);
		}
	}
	void grabInputs() {
		for (int x = 0; x < 4; x++) {
			if (!this->enablesysPads[x])
				this->adjustsysPads[x] = false;
			if (!this->enableControllerChangeSysPadDisplay)
				return;
			if ((this->sysPads[x].InstantInput & 2) && enablesysPads[x] && adjustsysPads[x])
				adjustsysPads[x] = false;
			else if ((this->sysPads[x].InstantInput & 2) && enablesysPads[x] && !adjustsysPads[x])
				adjustsysPads[x] = true;
			if (this->sysPads[x].HeldInput & 2)
				sysPadSelectIndex[x] += 1.0f;
			else
				sysPadSelectIndex[x] = 0;

			if (this->sysPadSelectIndex[x] >= ImGui::GetIO().Framerate * 0.5f) {
				if (enablesysPads[x] == true) {
					enablesysPads[x] = false;
					sysPadSelectIndex[x] = 0;
				}
				else if (enablesysPads[x] == false) {
					enablesysPads[x] = true;
					sysPadSelectIndex[x] = 0;
				}
			}
		}
	}
	void grabDuelInputs() {
		for (int x = 0; x < 2; x++) {
			__int64 retval = ccGame_GetPlayerLeader(x);
			if (!this->enableduelPads[x])
				this->adjustduelPads[x] = false;
			if (retval == 0 || !this->enableControllerChangeDuelPadDisplay)
				return;
			__int64 inputPointer = retval + 0x218;
			playerpadanalog analog = *reinterpret_cast<playerpadanalog*>(inputPointer + 0x614 - 40);
			DWORD instantinput = *(DWORD*)(inputPointer + 0x404);
			DWORD faceinput = *(DWORD*)(inputPointer + 0x408);
			if ((instantinput & 1) && enableduelPads[x] && adjustduelPads[x])
				adjustduelPads[x] = false;
			else if ((instantinput & 1) && enableduelPads[x] && !adjustduelPads[x])
				adjustduelPads[x] = true;
			if (this->sysPads[x].HeldInput & 1)
				duelPadSelectIndex[x] += 1.0f;
			else
				duelPadSelectIndex[x] = 0;
			if (this->duelPadSelectIndex[x] >= ImGui::GetIO().Framerate * 0.5f) {
				if (enableduelPads[x] == true) {
					enableduelPads[x] = false;
					duelPadSelectIndex[x] = 0;
				}
				else if (enableduelPads[x] == false) {
					enableduelPads[x] = true;
					duelPadSelectIndex[x] = 0;
				}
			}
		}
	}
	void createsysPadWindow(std::string name, pad controller, int padNum, bool* open, bool* adjust);
	void createduelPadWindow(std::string name, int padNum, bool* open, bool* adjust);
	void initTextures();
	void runMenu();
	std::vector<controllertexture> textures;
	pad sysPads[4] = { pad(), pad(), pad(), pad() };
	bool enableControllerChangeSysPadDisplay = true;
	bool enableControllerChangeDuelPadDisplay = true;
	private:
		std::vector<int> inputs = { NULL, 16384, 8192, 32768, 4096, 1024, 2048, 256, 512, 16, 64, 128, 32, 8, 1};//2: L3, 4: R3
		bool adjustsysPads[4] = { false, false, false, false };
		bool adjustduelPads[2] = { false, false };
		float sysPadSelectIndex[4] = { 0, 0, 0, 0 };
		float duelPadSelectIndex[2] = { 0, 0 };
		int textureindex = 0;
		bool enablesysPads[4] = { false, false, false, false };
		bool enableduelPads[2] = { false, false };
		ImVec2 sysPad1size;
		ImVec2 duelPad1size;
};