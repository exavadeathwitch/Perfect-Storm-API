#include "pch.hpp"

#include "DebugTitle.hpp"

#include "Core/DebugMenu/DebugMenu.hpp"

#include "Core/DebugMenu/MenuMessage/MenuMessage.hpp"
bool open = true;
void DebugTitle::runDebugTitle() {
	if (!runTitle)
		return;
	switch (c.autoboot) {
	case 1:
		runTitle = false;
		return;
	case 2:
		skipOpening = true;
		runTitle = false;
		return;
	case 3:
		bootFB = true;
		runTitle = false;
		return;
	default:
		break;
	}
	ImGuiStyle* style = &ImGui::GetStyle();;
	style->Colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	ImGuiIO io = ImGui::GetIO();
	ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y));
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	static ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar;
	ImGui::Begin("a", &open, flags);
	ImGui::End();
	ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y));
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::Begin("b", &open, flags);
	if (ImGui::Button((debugmessageset.getMessage(0).getconverted()).c_str()))
		runTitle = false;
	if (ImGui::Button((debugmessageset.getMessage(1).getconverted()).c_str())) {
		skipOpening = true;
		runTitle = false;
	}
	if (ImGui::Button((debugmessageset.getMessage(2).getconverted()).c_str())) {
		bootFB = true;
		runTitle = false;
	}
	ImGui::End();
}