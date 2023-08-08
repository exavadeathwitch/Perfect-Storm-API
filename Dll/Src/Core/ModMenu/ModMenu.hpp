#pragma once

#include "pch.hpp"
#include "Core/Globals.hpp"
#include "imgui/include/imgui.h"
#include "imguistyles/imgui_styles.h"
#include "imguiwidget/widget.hpp"
#include "Core/Mod/Mod.hpp"
#include "Core/MenuMessage/MenuMessage.hpp"

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
		ImGuiKey menukey;// = ImGuiKey_Escape;
		bool enableMenu = false;
		bool enableSettingsMenu = false;
		bool ModCredits = false;
		bool ec = true;
		bool convertmenumessages = false;
		std::string lang = "English";
		int langindex = 0;
		std::vector<Mod> mods;
		int maxMods;
		std::vector<Mod> imguimods;
		std::string langarr[13] = { "English", "French", "Italian", "German", "Spanish", "Arabic", "Polish", "Russian", "Japanese", "Portuguese", "Thai", "Korean", "Chinese(Traditional)" };

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
	void toggleSettingsMenu() {
		if (enableSettingsMenu)
			enableSettingsMenu = false;
		else
			enableSettingsMenu = true;
	}
	void setLang(std::string newlang) {
		for (int x = 0; x < 13; x++) {
			if (langarr[x] == newlang) {
				langindex = x;
				lang = newlang;
			}
		}
	}
	void runSettingsMenu() {
		if (!this->enableSettingsMenu)
			return;
		ImGui::Begin(debugmessageset.getMessage(1).getconverted().c_str(), &this->enableSettingsMenu);
		if (ImGui::BeginCombo(debugmessageset.getMessage(10).getconverted().c_str(), this->langarr[this->langindex].c_str())) // The second parameter is the label previewed before opening the combo.
		{
			for (int n = 0; n < IM_ARRAYSIZE(this->langarr); n++)
			{
				bool is_selected = (this->langarr[this->langindex].c_str() == this->langarr[n].c_str()); // You can store your selection however you want, outside or inside your objects
				if (ImGui::Selectable(this->langarr[n].c_str(), is_selected)) {
					settings::updateSettings();
					this->langindex = n;
					menuSet.setlang(this->langarr[n]);
					translateAllSets();
				}
				if (is_selected)
					ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
			}
			ImGui::EndCombo();
		}
		ImGui::SameLine(); widget::HelpMarker(debugmessageset.getMessage(11).getconverted().c_str());
		if (ImGui::Button(debugmessageset.getMessage(2).getconverted().c_str())) {
			settings::updateSettings();
			settings::save();
			ImGui::SaveStylesTo(util::getImguiStylePath().string().c_str());
		}
		if (ImGui::Checkbox(debugmessageset.getMessage(12).getconverted().c_str(), &convertmenumessages)) {
			settings::updateSettings();
			if (convertmenumessages) {
				for (int x = 0; x < debugmessageset.size; x++) {
					debugmessageset.messages[x].convertmessages = true;
				}
			}
			else {
				for (int x = 0; x < debugmessageset.size; x++) {
					debugmessageset.messages[x].convertmessages = false;
				}
			}
		}
		ImGui::SameLine(); widget::HelpMarker(debugmessageset.getMessage(13).getconverted().c_str());
		if (ImGui::Checkbox(debugmessageset.getMessage(5).getconverted().c_str(), &ec))
			settings::updateSettings();
		ImGui::SameLine(); widget::HelpMarker(debugmessageset.getMessage(6).getconverted().c_str());
		if (ImGui::InputInt(debugmessageset.getMessage(7).getconverted().c_str(), &maxMods))
			settings::updateSettings();
		if (maxMods < 2)
			maxMods = 2;
		if (maxMods > 10)
			maxMods = 10;
		ImGui::SameLine(); widget::HelpMarker(debugmessageset.getMessage(8).getconverted().c_str());
		ImGui::Text("\n");
		ImGui::Text(debugmessageset.getMessage(3).getconverted().c_str());
		ImGui::SameLine(); widget::HelpMarker(debugmessageset.getMessage(4).getconverted().c_str());
		ImGui::ShowStyleEditor();
		ImGui::End();
	}
	void runMenu() {
		if (maxMods < 2)
			maxMods = 2;
		if (maxMods > 10)
			maxMods = 10;
		this->runModCredits();
		this->runSettingsMenu();
		
		if (!enableMenu)
			return;
		ImGui::BeginMainMenuBar();
		if (ImGui::BeginMenu("Storm API"))
		{
			if (ImGui::MenuItem(debugmessageset.getMessage(0).getconverted().c_str(), "")) { this->toggleMenu(); }
			if (ImGui::MenuItem(debugmessageset.getMessage(1).getconverted().c_str(), "")) { this->toggleSettingsMenu(); }
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
			if (ImGui::BeginMenu((debugmessageset.getMessage(9).getconverted() + modstring).c_str()))
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