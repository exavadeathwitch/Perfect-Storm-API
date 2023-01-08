#include "pch.hpp"

#include "Render.hpp"

#include "imguiwidget/widget.hpp"

#include "Core/DebugMenu/MenuMessage/MenuMessage.hpp"

void Render::runMenu() {
	ImGui::Text(rendermessageset.getMessage(0).getconverted().c_str());
	ImGui::SameLine(); widget::HelpMarker(rendermessageset.getMessage(1).getconverted().c_str());
	for (int i = 0; i < sizeof(enablelayer); i++) {
		bool orig = enablelayer[i];
		ImGui::Checkbox(layers[i].c_str(), &orig);
		enablelayer[i] = orig;
	}
	ImGui::Checkbox("HUD", &enableHud);
	ImGui::SameLine(); widget::HelpMarker(rendermessageset.getMessage(2).getconverted().c_str());
}