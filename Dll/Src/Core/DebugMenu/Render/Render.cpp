#include "pch.hpp"

#include "Render.hpp"

#include "imguiwidget/widget.hpp"

void Render::runMenu() {
	ImGui::Text("Render Layers");
	ImGui::SameLine(); widget::HelpMarker("The boxes below determine what layers of the game will render.");
	for (int i = 0; i < sizeof(enablelayer); i++) {
		bool orig = enablelayer[i];
		ImGui::Checkbox(layers[i].c_str(), &orig);
		enablelayer[i] = orig;
	}
	ImGui::Checkbox("HUD", &enableHud);
	ImGui::SameLine(); widget::HelpMarker("This checkbox controls whether the HUD is enabled.\nThis will crash the game if activated for too long during a match in any battle game mode.");
}