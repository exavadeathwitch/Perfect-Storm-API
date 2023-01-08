#include "pch.hpp"

#include "Util/Memory/String.hpp"

#include "controllerUI.hpp"

#include "imgui/include/imgui.h"

#include "imgui/include/imgui_internal.h"

#include "Class/gamepad.hpp"

void controllerUI::initTextures() {
		this->textures.clear();
		std::string path = util::getModPath().generic_string() + "\\ui\\controllerUI\\";
		std::replace(path.begin(), path.end(), '/', '\\');
		for (auto& p : std::filesystem::recursive_directory_iterator(path)) {
			controllertexture newtextures;
			bool valid = false;
			float analogmovement = 450.0f;
			if (p.is_directory()) {
				std::string folder = path + p.path().filename().string() + "\\";
				for (int x = 0; x < size(controllerfilenames); x++) {
					std::ifstream f(folder + controllerfilenames[x]);
					if (!f.good()) 
						break;
					newtextures.addtexture(texture(0, 0, folder + controllerfilenames[x], true));
				}
				if (newtextures.gettexturesize() == 21)
					valid = true;
				std::ifstream f(folder + "analog.txt");
				if (!f.good())
					break;
				if (f.is_open())
				{
					std::string line;
					while (std::getline(f, line))
					{
						analogmovement = stof(line);
						break;
					}
					f.close();
				}

			}
			if (valid) {
				newtextures.setname(p.path().filename().string());
				newtextures.setanalogmovement(analogmovement);
				this->textures.push_back(newtextures);
			}
		}
		this->loadTextures();
	}
void controllerUI::createsysPadWindow(std::string name, pad controller, int padNum, bool* open, bool* adjust) {
	ImGuiWindowFlags window_flags = 0;
	if (!*adjust) {
		window_flags |= ImGuiWindowFlags_NoResize;
		window_flags |= ImGuiWindowFlags_NoBackground;
	}
	window_flags |= ImGuiWindowFlags_NoTitleBar;
	window_flags |= ImGuiWindowFlags_NoScrollbar;
	window_flags |= ImGuiWindowFlags_NoScrollWithMouse;
	ImGuiWindowFlags window_flags2 = 0;

	window_flags2 |= ImGuiWindowFlags_NoBackground;
	window_flags2 |= ImGuiWindowFlags_NoTitleBar;
	window_flags2 |= ImGuiWindowFlags_NoResize;
	window_flags2 |= ImGuiWindowFlags_NoScrollbar;
	window_flags2 |= ImGuiWindowFlags_NoScrollWithMouse;
	std::cout << name << std::endl;
	ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize[0] / 2, ImGui::GetIO().DisplaySize[1] / 2), ImGuiCond_FirstUseEver);
	ImGui::Begin((name).c_str(), NULL, window_flags);
	float texturedivisor = 1440 / ((ImGui::GetWindowHeight() + ImGui::GetWindowWidth()) / 2);
	float newhpos = ImGui::GetWindowHeight();
	float newwpos = ImGui::GetWindowWidth();
	ImGui::SetWindowSize(ImVec2(ImGui::GetWindowHeight() * 1.5f, ImGui::GetWindowHeight()));
	newhpos = ImGui::GetWindowHeight();
	newwpos = ImGui::GetWindowWidth();
	ImVec2 newpos = ImGui::GetWindowPos();
	ImVec2 newsize = ImGui::GetWindowSize();
	texturedivisor = 1440 / ((ImGui::GetWindowHeight() + ImGui::GetWindowWidth()) / 2);
	ImGui::End();
	float analogdivisor = texturedivisor * this->textures[textureindex].analogmovement;
	bool enableleftanalog = true;
	bool enablerightanalog = true;
	if (padNum == 0)
		sysPad1size = newsize;
	ImGui::SetNextWindowPos(newpos);
	ImGui::SetNextWindowSize(newsize);
	ImGui::Begin((name).c_str(), NULL, window_flags);
	ImGui::Image((void*)this->textures[textureindex].gettexture(17 + padNum).my_texture, ImVec2(this->textures[textureindex].gettexture(17 + padNum).width / texturedivisor, this->textures[textureindex].gettexture(17 + padNum).height / texturedivisor));
	//std::cout << *adjust << std::endl;
	ImGui::End();

	if (*adjust)
		return;
	
	if (controller.leftanalogdown > 0 || controller.leftanalogleft > 0 || controller.leftanalogright > 0 || controller.leftanalogup > 0) {
		float xoffset = ((float)controller.leftanalogright / analogdivisor) - ((float)controller.leftanalogleft / analogdivisor);
		float yoffset = ((float)controller.leftanalogdown / analogdivisor) - ((float)controller.leftanalogup / analogdivisor);
		ImVec2 coords = newpos;
		float x = coords.x;
		float y = coords.y;
		ImGui::SetNextWindowPos(ImVec2(coords.x + xoffset, coords.y + yoffset));
		ImGui::SetNextWindowSize(newsize);
		ImGui::Begin((name + textures[textureindex].gettexture(15).path).c_str(), NULL, window_flags2);
		ImGui::Image((void*)textures[textureindex].gettexture(15).my_texture, ImVec2(textures[textureindex].gettexture(15).width / texturedivisor, textures[textureindex].gettexture(15).height / texturedivisor));
		ImGui::End();
	}

	if (controller.rightanalogdown > 0 || controller.rightanalogleft > 0 || controller.rightanalogright > 0 || controller.rightanalogup > 0) {
		float xoffset = ((float)controller.rightanalogright / analogdivisor) - ((float)controller.rightanalogleft / analogdivisor);
		float yoffset = ((float)controller.rightanalogdown / analogdivisor) - ((float)controller.rightanalogup / analogdivisor);
		ImVec2 coords = newpos;
		float x = coords.x;
		float y = coords.y;
		ImGui::SetNextWindowPos(ImVec2(coords.x + xoffset, coords.y + yoffset));
		ImGui::SetNextWindowSize(newsize);
		ImGui::Begin((name + textures[textureindex].gettexture(16).path).c_str(), NULL, window_flags2);
		ImGui::Image((void*)textures[textureindex].gettexture(16).my_texture, ImVec2(textures[textureindex].gettexture(16).width / texturedivisor, textures[textureindex].gettexture(16).height / texturedivisor));
		ImGui::End();
	}

	for (int x = 1; x < inputs.size(); x++) {
		if (controller.HeldInput & inputs[x]) {
			ImGui::SetNextWindowPos(newpos);
			ImGui::SetNextWindowSize(newsize);
			ImGui::Begin((name + textures[textureindex].gettexture(x).path).c_str(), NULL, window_flags2);
			ImGui::Image((void*)textures[textureindex].gettexture(x).my_texture, ImVec2(textures[textureindex].gettexture(x).width / texturedivisor, textures[textureindex].gettexture(x).height / texturedivisor));
			ImGui::End();
		}
	}

}
void controllerUI::runMenu() {
	if (ImGui::BeginCombo("Controller Type", this->textures[this->textureindex].getname().c_str())) // The second parameter is the label previewed before opening the combo.
	{
		for (int n = 0; n < this->textures.size(); n++)
		{
			bool is_selected = (this->textures[this->textureindex].getname().c_str() == this->textures[n].getname().c_str()); // You can store your selection however you want, outside or inside your objects
			if (ImGui::Selectable(this->textures[n].getname().c_str(), is_selected))
				this->textureindex = n;
			if (is_selected)
				ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
		}
		ImGui::EndCombo();
	}
	ImGui::Text("Local Controller Inputs");
	if (ImGui::Button("Match Local Pad 1 Size")) {
		for (int x = 0; x < sizeof(this->enablesysPads); x++) {
			ImGui::SetWindowSize(("Pad " + std::to_string(x)).c_str(), this->sysPad1size);
		}
	}
	for (int x = 0; x < sizeof(this->enablesysPads); x++) {
		ImGui::Checkbox(std::to_string(x + 1).c_str(), &enablesysPads[x]);
		ImGui::SameLine();
		if (ImGui::Button(("Toggle Adjust Pad " + std::to_string(x + 1)).c_str())) {
			if (this->adjustsysPads[x] == true)
				this->adjustsysPads[x] = false;
			else
				this->adjustsysPads[x] = true;
		}
	}
	ImGui::Text("Battle Inputs");
	if (ImGui::Button("Match Battle Pad 1 Size")) {
		for (int x = 0; x < sizeof(this->enableduelPads); x++) {
			ImGui::SetWindowSize((std::to_string(x) + "duel").c_str(), this->duelPad1size);
		}
	}
	for (int x = 0; x < sizeof(this->enableduelPads); x++) {
		ImGui::Checkbox((std::to_string(x + 1) + " ").c_str(), &enableduelPads[x]);
		ImGui::SameLine();
		if (ImGui::Button(("Toggle Adjust Battle Pad " + std::to_string(x + 1)).c_str())) {
			if (this->adjustduelPads[x] == true)
				this->adjustduelPads[x] = false;
			else
				this->adjustduelPads[x] = true;
		}
	}
	if (ImGui::Button("Reload Files")) {
		this->initTextures();
		this->loadTextures();
	}
}
void controllerUI::createduelPadWindow(std::string name, int padNum, bool* open, bool* adjust) {
	__int64 retval = ccGame_GetPlayerLeader(padNum);
	bool nobuttons = false;
	if (retval == 0)
		nobuttons = true;
	//if (playernum == 1) {
		//*(double*)(retval + 0xB40) = 0;
		//*(DWORD*)(retval + 0x840) = 1;
	//}
	ImGuiWindowFlags window_flags = 0;
	if (!*adjust) {
		window_flags |= ImGuiWindowFlags_NoResize;
		window_flags |= ImGuiWindowFlags_NoBackground;
	}
	window_flags |= ImGuiWindowFlags_NoTitleBar;
	window_flags |= ImGuiWindowFlags_NoScrollbar;
	window_flags |= ImGuiWindowFlags_NoScrollWithMouse;
	ImGuiWindowFlags window_flags2 = 0;

	window_flags2 |= ImGuiWindowFlags_NoBackground;
	window_flags2 |= ImGuiWindowFlags_NoTitleBar;
	window_flags2 |= ImGuiWindowFlags_NoResize;
	window_flags2 |= ImGuiWindowFlags_NoScrollbar;
	window_flags2 |= ImGuiWindowFlags_NoScrollWithMouse;

	ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize[0] / 2, ImGui::GetIO().DisplaySize[1] / 2), ImGuiCond_FirstUseEver);
	ImGui::Begin((name).c_str(), NULL, window_flags);
	float texturedivisor = 1440 / ((ImGui::GetWindowHeight() + ImGui::GetWindowWidth()) / 2);
	float newhpos = ImGui::GetWindowHeight();
	float newwpos = ImGui::GetWindowWidth();
	ImGui::SetWindowSize(ImVec2(ImGui::GetWindowHeight() * 1.5f, ImGui::GetWindowHeight()));
	newhpos = ImGui::GetWindowHeight();
	newwpos = ImGui::GetWindowWidth();
	ImVec2 newpos = ImGui::GetWindowPos();
	ImVec2 newsize = ImGui::GetWindowSize();
	texturedivisor = 1440 / ((ImGui::GetWindowHeight() + ImGui::GetWindowWidth()) / 2);
	ImGui::End();
	float analogdivisor = texturedivisor * this->textures[textureindex].analogmovement;

	if (padNum == 0)
		duelPad1size = newsize;
	ImGui::SetNextWindowPos(newpos);
	ImGui::SetNextWindowSize(newsize);
	ImGui::Begin((name).c_str(), NULL, window_flags);
	ImGui::Image((void*)this->textures[textureindex].gettexture(17 + padNum).my_texture, ImVec2(this->textures[textureindex].gettexture(17 + padNum).width / texturedivisor, this->textures[textureindex].gettexture(17 + padNum).height / texturedivisor));
	//std::cout << *adjust << std::endl;
	ImGui::End();

	if (*adjust || retval == 0)
		return;

	std::cout << padNum << std::endl;
	std::cout << std::hex << retval << std::endl;
	__int64 inputPointer = retval + 0x218;
	playerpadanalog analog = *reinterpret_cast<playerpadanalog*>(inputPointer + 0x5EC);
	DWORD instantinput = *(DWORD*)(inputPointer + 0x404);
	DWORD faceinput = *(DWORD*)(inputPointer + 0x408);
	float leftstickpress = *(float*)(retval + 0x220);
	short leftstickrotation = *(short*)(retval + 0x22A);
	float rightstickpress = *(float*)(retval + 0x328);
	short rightstickrotation = *(short*)(retval + 0x338);
	/*
	if (instantinput & 1) {
		if (*adjust)
			*adjust = false;
		else
			*adjust = true;
	}*/
	playerpadanalog a;
	a.leftanalogdown = 0;
	a.leftanalogup = 0;
	a.leftanalogleft = 0;
	a.leftanalogright = 0;
	a.rightanalogdown = 0;
	a.rightanalogup = 0;
	a.rightanalogleft = 0;
	a.rightanalogright = 0;
	if (*(float*)(retval + 0x220) > 0 || *(uint8_t*)(inputPointer + 0x40A) > 0) {
		switch (*(uint8_t*)(inputPointer + 0x40A)) {
		case 0x10: //Up
			a.leftanalogup = short(leftstickpress * 32767.0f);
			break;
		case 0x50: //Up Left
			a.leftanalogleft = short(leftstickpress * 32767.0f);
			a.leftanalogup = short(leftstickpress * 32767.0f);
			break;
		case 0x40: //Left
			std::cout << "Left\n";
			a.leftanalogleft = short(leftstickpress * 32767.0f);
			break;
		case 0x60: //Down Left
			a.leftanalogleft = short(leftstickpress * 32767.0f);
			a.leftanalogdown = short(leftstickpress * 32767.0f);
			break;
		case 0x20: //Down
			a.leftanalogdown = short(leftstickpress * 32767.0f);
			break;
		case 0xA0: //Down Right
			a.leftanalogdown = short(leftstickpress * 32767.0f);
			a.leftanalogright = short(leftstickpress * 32767.0f);
			break;
		case 0x80: //Right
			a.leftanalogright = short(leftstickpress * 32767.0f);
			break;
		case 0x90: //Up Right
			a.leftanalogup = short(leftstickpress * 32767.0f);
			a.leftanalogright = short(leftstickpress * 32767.0f);
			break;
		}
		float xoffset = ((float)a.leftanalogright / analogdivisor) - ((float)a.leftanalogleft / analogdivisor);
		float yoffset = ((float)a.leftanalogdown / analogdivisor) - ((float)a.leftanalogup / analogdivisor);
		ImVec2 coords = newpos;
		float x = coords.x;
		float y = coords.y;
		ImGui::SetNextWindowPos(ImVec2(coords.x + xoffset, coords.y + yoffset));
		ImGui::SetNextWindowSize(newsize);
		ImGui::Begin((name + textures[textureindex].gettexture(15).path + "duel").c_str(), NULL, window_flags2);
		ImGui::Image((void*)textures[textureindex].gettexture(15).my_texture, ImVec2(textures[textureindex].gettexture(15).width / texturedivisor, textures[textureindex].gettexture(15).height / texturedivisor));
		ImGui::End();
	}
	if (*(float*)(retval + 0x328) > 0 || *(uint8_t*)(inputPointer + 0x40B) > 0) {
		switch (*(uint8_t*)(inputPointer + 0x40B) * 0x10) {
		case 0x10: //Up
			a.rightanalogup = short(rightstickpress * 32767.0f);
			break;
		case 0x50: //Up Left
			a.rightanalogleft = short(rightstickpress * 32767.0f);
			a.rightanalogup = short(rightstickpress * 32767.0f);
			break;
		case 0x40: //Left
			a.rightanalogleft = short(rightstickpress * 32767.0f);
			break;
		case 0x60: //Down Left
			a.rightanalogleft = short(rightstickpress * 32767.0f);
			a.rightanalogdown = short(rightstickpress * 32767.0f);
			break;
		case 0x20: //Down
			a.rightanalogdown = short(rightstickpress * 32767.0f);
			break;
		case 0xA0: //Down Right
			a.rightanalogdown = short(rightstickpress * 32767.0f);
			a.rightanalogright = short(rightstickpress * 32767.0f);
			break;
		case 0x80: //Right
			a.rightanalogright = short(rightstickpress * 32767.0f);
			break;
		case 0x90: //Up Right
			a.rightanalogup = short(rightstickpress * 32767.0f);
			a.rightanalogright = short(rightstickpress * 32767.0f);
			break;
		}
		float xoffset = ((float)a.rightanalogright / analogdivisor) - ((float)a.rightanalogleft / analogdivisor);
		float yoffset = ((float)a.rightanalogdown / analogdivisor) - ((float)a.rightanalogup / analogdivisor);
		ImVec2 coords = newpos;
		float x = coords.x;
		float y = coords.y;
		ImGui::SetNextWindowPos(ImVec2(coords.x + xoffset, coords.y + yoffset));
		ImGui::SetNextWindowSize(newsize);
		ImGui::Begin((name + textures[textureindex].gettexture(16).path + "duel").c_str(), NULL, window_flags2);
		ImGui::Image((void*)textures[textureindex].gettexture(16).my_texture, ImVec2(textures[textureindex].gettexture(16).width / texturedivisor, textures[textureindex].gettexture(16).height / texturedivisor));
		ImGui::End();
	}

	for (int x = 1; x < inputs.size(); x++) {
		if (faceinput & inputs[x]) {
			ImGui::SetNextWindowPos(newpos);
			ImGui::SetNextWindowSize(newsize);
			ImGui::Begin((name + textures[textureindex].gettexture(x).path + "duel").c_str(), NULL, window_flags2);
			ImGui::Image((void*)textures[textureindex].gettexture(x).my_texture, ImVec2(textures[textureindex].gettexture(x).width / texturedivisor, textures[textureindex].gettexture(x).height / texturedivisor));
			ImGui::End();
		}
	}
}