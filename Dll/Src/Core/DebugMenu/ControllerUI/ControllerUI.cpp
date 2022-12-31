#include "pch.hpp"

#include <iostream>

#include "Util/Memory/String.hpp"

#include "controllerUI.hpp"

#include "imgui/include/imgui.h"

#include "Class/gamepad.hpp"

int display[] = {0, 0};
void ns4::controllerUI::controllerDisplay() {

	typedef signed __int64(__fastcall* ccGame_GetPlayerLeader) (unsigned int a1);
	ccGame_GetPlayerLeader occGame_GetPlayerLeader = (ccGame_GetPlayerLeader)(globals::moduleBase + 0x85A948 + 0xC00);
	for (int playernum = 0; playernum < 2; playernum++) {
		__int64 retval = occGame_GetPlayerLeader(playernum);
		if (retval == 0) {
			std::cout << "return\n";
			return;
		}
		/*
		if (playernum == 1) {
			*(double*)(retval + 0xB40) = 0;
			*(DWORD*)(retval + 0x840) = 1;
		}*/
		__int64 inputPointer = retval + 0x218;
		DWORD instantinput = *(DWORD*)(inputPointer + 0x404);
		DWORD faceinput = *(DWORD*)(inputPointer + 0x408);
		//std::cout << "player " << playernum << std::endl;
		//std::cout << std::hex << inputPointer << std::endl;
		if (instantinput & 1) {
			if (display[playernum] == 1)
				display[playernum] = 0;
			else
				display[playernum] = 1;
		}
		if (display[playernum] == 1) {
			playerpadanalog analog = *reinterpret_cast<playerpadanalog*>(inputPointer + 0x614 - 40);
			float texturedivisor = 2;
			ImGuiWindowFlags window_flags = 0;

			window_flags |= ImGuiWindowFlags_NoBackground;
			window_flags |= ImGuiWindowFlags_NoTitleBar;
			//window_flags |= ImGuiWindowFlags_NoResize;
			window_flags |= ImGuiWindowFlags_NoScrollbar;
			window_flags |= ImGuiWindowFlags_NoScrollWithMouse;
			ImGuiWindowFlags window_flags2 = 0;

			window_flags2 |= ImGuiWindowFlags_NoBackground;
			window_flags2 |= ImGuiWindowFlags_NoTitleBar;
			window_flags2 |= ImGuiWindowFlags_NoResize;
			window_flags2 |= ImGuiWindowFlags_NoScrollbar;
			window_flags2 |= ImGuiWindowFlags_NoScrollWithMouse;
			//ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f), 0, ImVec2(0.0f, 0.0f));
			//ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
			ImGui::Begin((std::to_string(playernum)).c_str(), NULL, window_flags);
			std::cout << std::to_string(playernum) << std::endl;
			texturedivisor = 1440 / ((ImGui::GetWindowHeight() + ImGui::GetWindowWidth()) / 2);
			float newhpos = ImGui::GetWindowHeight();
			float newwpos = ImGui::GetWindowWidth();
			ImGui::SetWindowSize(ImVec2(ImGui::GetWindowHeight() * 1.5f, ImGui::GetWindowHeight()));
			newhpos = ImGui::GetWindowHeight();
			newwpos = ImGui::GetWindowWidth();
			ImVec2 newpos = ImGui::GetWindowPos();
			ImVec2 newsize = ImGui::GetWindowSize();
			texturedivisor = 1440 / ((ImGui::GetWindowHeight() + ImGui::GetWindowWidth()) / 2);
			ImGui::End();

			float analogdivisor = texturedivisor * 450.0f;
			bool enableleftanalog = true;
			bool enablerightanalog = true;

			ImGui::SetNextWindowPos(newpos);
			ImGui::SetNextWindowSize(newsize);
			ImGui::Begin((std::to_string(playernum)).c_str(), NULL, window_flags2);
			ImGui::Image((void*)textures[0].my_texture, ImVec2(textures[0].width / texturedivisor, textures[0].height / texturedivisor));
			ImGui::End();
			
			if (analog.leftanalogdown > 0 || analog.leftanalogleft > 0 || analog.leftanalogright > 0 || analog.leftanalogup > 0) {
				float xoffset = ((float)analog.leftanalogright / analogdivisor) - ((float)analog.leftanalogleft / analogdivisor);
				float yoffset = ((float)analog.leftanalogdown / analogdivisor) - ((float)analog.leftanalogup / analogdivisor);
				ImVec2 coords = newpos;
				float x = coords.x;
				float y = coords.y;
				ImGui::SetNextWindowPos(ImVec2(coords.x + xoffset, coords.y + yoffset));
				ImGui::SetNextWindowSize(newsize);
				std::cout << std::to_string(playernum) + textures[15].path << std::endl;
				ImGui::Begin((std::to_string(playernum) + textures[15].path).c_str(), NULL, window_flags2);
				ImGui::Image((void*)textures[15].my_texture, ImVec2(textures[15].width / texturedivisor, textures[15].height / texturedivisor));
				ImGui::End();
			}

			if (analog.rightanalogdown > 0 || analog.rightanalogleft > 0 || analog.rightanalogright > 0 || analog.rightanalogup > 0) {
				float xoffset = ((float)analog.rightanalogright / analogdivisor) - ((float)analog.rightanalogleft / analogdivisor);
				float yoffset = ((float)analog.rightanalogdown / analogdivisor) - ((float)analog.rightanalogup / analogdivisor);
				ImVec2 coords = newpos;
				float x = coords.x;
				float y = coords.y;
				ImGui::SetNextWindowPos(ImVec2(coords.x + xoffset, coords.y + yoffset));
				ImGui::SetNextWindowSize(newsize);
				std::cout << std::to_string(playernum) + textures[16].path << std::endl;
				ImGui::Begin((std::to_string(playernum) + textures[16].path).c_str(), NULL, window_flags2);
				ImGui::Image((void*)textures[16].my_texture, ImVec2(textures[16].width / texturedivisor, textures[16].height / texturedivisor));
				ImGui::End();
			}

			for (int x = 1; x < inputs.size(); x++) {
				if (faceinput & inputs[x]) {
					ImGui::SetNextWindowPos(newpos);
					ImGui::SetNextWindowSize(newsize);
					std::cout << std::to_string(playernum) + textures[x].path << std::endl;
					ImGui::Begin((std::to_string(playernum) + textures[x].path).c_str(), NULL, window_flags2);
					ImGui::Image((void*)textures[x].my_texture, ImVec2(textures[x].width / texturedivisor, textures[x].height / texturedivisor));
					ImGui::End();
				}
			}
		}
	}
}