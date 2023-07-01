#pragma once

#include "pch.hpp"
#include "imgui/include/imgui.h"
#include "Core/Mod/Mod.hpp"
class ModName {
public:
	std::string name;
	std::string description;
	std::string author;
	ModName() {

	}
	ModName(std::string name, std::string description, std::string author) {
		this->name = name;
		this->description = description;
		this->author = author;
	}
};
class ModMenu {
	public:
		ImGuiKey menukey = ImGuiKey_Escape;
		bool enableMenu = false;
		bool ModCredits = false;
		std::vector<Mod> mods;
		int maxMods;
		std::vector<Mod> imguimods;
		ModMenu() {

		}
		void initializeModNames(std::vector<Mod> Mod) {
			for (int x = 0; x < Mod.size(); x++) {
				mods.push_back(Mod[x]);
				typedef void(__stdcall* f)();
				f twv = (f)GetProcAddress(mods[x].dll, "toggleWindowValue");
				if (twv)
					imguimods.push_back(Mod[x]);
			}
		}
	void runMenu() {
		if (maxMods < 1)
			maxMods = 6;
		this->runModCredits();
		if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(menukey))) {
			if (enableMenu)
				enableMenu = false;
			else
				enableMenu = true;
		}
		if (!enableMenu)
			return;
		ImGui::BeginMainMenuBar();
		if (ImGui::BeginMenu("Storm API"))
		{
			if (ImGui::MenuItem("Installed Mods", "")) { this->toggleMenu(); }
			ImGui::EndMenu();
		}
		int multiplycount = 0;
		int modcount = 1;
		std::string modstring = "";
		if (imguimods.size() == 0)
			return;

		int modsize = this->maxMods;
		if (this->imguimods.size() < modsize)
			modsize = this->imguimods.size();
		int modstart = 0;
		while (multiplycount * this->maxMods < imguimods.size()) {
			int modsran = 0;
			if (ImGui::BeginMenu(("Mods" + modstring).c_str()))
			{
				for (int x = modstart; x < this->imguimods.size(); x++) {
					if (x >= modsize * modcount)
						break;
					typedef void(__stdcall* f)();
					f twv = (f)GetProcAddress(imguimods[x].dll, "toggleWindowValue");
					if (ImGui::MenuItem(imguimods[x].name.c_str(), ""))
						twv();
					modsran++;
				}
				ImGui::EndMenu();
			}
			modstart += modsize;
			modcount++;
			modstring = " " + std::to_string(modcount);
			multiplycount++;
			if (this->imguimods.size() < modsize)
				modsize = this->imguimods.size();
		}
		ImGui::EndMainMenuBar();
		/*
		while (multiplycount * this->maxMods < imguimods.size()) {
			if (ImGui::BeginMenu(("Mods" + modstring).c_str()))
			{
				int count = multiplycount * this->maxMods;
				for (int x = 0; x < this->maxMods; x++) {
					typedef void(__stdcall* f)();
					f twv = (f)GetProcAddress(imguimods[x + count].dll, "toggleWindowValue");
					if (ImGui::MenuItem(imguimods[x + count].name.c_str(), ""))
						twv();
				}
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
			multiplycount++;
		}
		*/
	}
	void toggleMenu() {
		if (ModCredits)
			ModCredits = false;
		else
			ModCredits = true;
	}
	void runModCredits() {
		if (ModCredits) {
			ImGui::Begin("Installed Mods", &this->ModCredits);
			for (int x = 0; x < mods.size(); x++)
				ImGui::Text((mods[x].name + " - " + mods[x].author + " - " + mods[x].description).c_str());
			ImGui::End();
		}
	}
};