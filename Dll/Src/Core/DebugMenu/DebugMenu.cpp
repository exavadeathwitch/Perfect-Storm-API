#include "pch.hpp"

#include "DebugMenu.hpp"

#include "GameSpeed/GameSpeed.hpp"
float framecount = 0;
void DebugMenu::runDebugMenu() {
	if (c.R3framestep && ImGui::IsKeyReleased(ImGuiKey_GamepadR3) && enableFrameStep)
		frameStep = true;
	if (c.R3framestep && ImGui::IsKeyDown(ImGuiKey_GamepadR3) && enableFrameStep && framecount >= 0.5 * ImGui::GetIO().Framerate) {
		enableFrameStep = false;
		framecount = 0;
	}
	if (c.R3framestep && ImGui::IsKeyPressed(ImGuiKey_GamepadR3, false) && !enableFrameStep)
		enableFrameStep = true;
	if (c.R3framestep && !ImGui::IsKeyDown(ImGuiKey_GamepadR3)) {
		framecount = 0;
	}
	framecount += 1.0f;
	if (!enableDebugMenu)
		return;
	ImGui::BeginMainMenuBar();
	if (ImGui::BeginMenu("General"))
	{
		if (ImGui::MenuItem("Game Speed", "")) { gs.toggleMenu(); }
		if (ImGui::MenuItem("Render", "")) { r.toggleMenu(); }
		if (ImGui::MenuItem("Config", "")) { c.toggleMenu(); }
		if (ImGui::MenuItem("Console", "")) { globals::modConsole->changeRender(); }
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Duel"))
	{
		if (ImGui::MenuItem("Input Display", "")) { NULL; }
		if (ImGui::MenuItem("Player Control", "")) { NULL; }
		if (ImGui::MenuItem("Customize Controls", "")) { NULL; }
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Roster"))
	{
		if (ImGui::MenuItem("Roster Coordinates", "")) { ro.toggleMenu(); }
		ImGui::EndMenu();
	}
	ImGui::EndMainMenuBar();
	gs.createMenu();
	r.createMenu();
	ro.createMenu();
	c.createMenu();
	globals::modConsole->render();
}