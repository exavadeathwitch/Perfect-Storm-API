#include "pch.hpp"

#include "DebugMenu.hpp"

#include "GameSpeed/GameSpeed.hpp"

void DebugMenu::runDebugMenu() {
	if (!enableDebugMenu)
		return;
	ImGui::BeginMainMenuBar();
	if (ImGui::BeginMenu("General"))
	{
		if (ImGui::MenuItem("Game Speed", "")) { gs.toggleMenu(); }
		if (ImGui::MenuItem("Console", "")) {globals::modConsole->changeRender(); }
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Duel"))
	{
		if (ImGui::MenuItem("Input Display", "")) { NULL; }
		if (ImGui::MenuItem("Player Control", "")) { NULL; }
		if (ImGui::MenuItem("Customize Controls", "")) { NULL; }
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Other"))
	{
		if (ImGui::MenuItem("Roster Coordinates", "")) { NULL; }
		ImGui::EndMenu();
	}
	gs.createMenu();
	ImGui::EndMainMenuBar();
}