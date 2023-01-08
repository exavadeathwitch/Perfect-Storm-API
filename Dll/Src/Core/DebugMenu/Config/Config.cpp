#include "pch.hpp"

#include "Config.hpp"

#include "imguiwidget/widget.hpp"

#include "Core/Settings/Settings.hpp"

#include "Core/DebugMenu/MenuMessage/MenuMessage.hpp"
void Config::runMenu() {
	if (ImGui::Button("Save Config"))
		settings::save();
	ImGui::SameLine();
	if (ImGui::Button("Load Config"))
		settings::load();
	//ImGui::Checkbox("Enable Frame Step with Controller", &R3framestep);
	//ImGui::Checkbox((menuSet.getTranslation("R3framestep")).c_str(), &R3framestep);
	ImGui::Checkbox("Enable Frame Step with Controller", &R3framestep);
	ImGui::SameLine(); widget::HelpMarker("This enables use of the R3 button on any connected gamepad to activate frame step.\nEnable Frame Step: Press R3\nFrame Step: Press R3 once in Frame Step mode\nDisable Frame Step: Hold R3");
	ImGui::Checkbox("Output xfbin to Console", &displayloadXFBIN);
	ImGui::SameLine(); widget::HelpMarker("This will print to the console each time an xfbin file is loaded.");
	ImGui::Checkbox("Enable Keyboard Direct Input", &enableKeyboard);
	ImGui::SameLine(); widget::HelpMarker("This enables direct input to the game from the keyboard.\nThis must be disabled for the input display to work properly.");
	if (ImGui::BeginCombo("Language", this->langarr[this->lang].c_str())) // The second parameter is the label previewed before opening the combo.
	{
		for (int n = 0; n < IM_ARRAYSIZE(this->langarr); n++)
		{
			bool is_selected = (this->langarr[this->lang].c_str() == this->langarr[n].c_str()); // You can store your selection however you want, outside or inside your objects
			if (ImGui::Selectable(this->langarr[n].c_str(), is_selected))
				this->lang = n;
				if (is_selected)
					ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
		}
		ImGui::EndCombo();
	}
	ImGui::SameLine(); widget::HelpMarker("This controls the language of this API.");
	if (ImGui::Button("Reload Debug Language Files"))
		translateAllSets();
	ImGui::Text("\n");
	ImGui::Text("Style Customizer");
	ImGui::SameLine(); widget::HelpMarker("The settings below can change the look of this interface.");
	ImGui::ShowStyleEditor();
}