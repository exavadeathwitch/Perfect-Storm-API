#include "pch.hpp"

#include "DebugMenu.hpp"

#include "GameSpeed/GameSpeed.hpp"
float framecount = 0;
bool init = false;
bool outofinitialize = false;
void DebugMenu::runDebugMenu() {
	
	if (c.R3framestep && ImGui::IsKeyReleased(ImGuiKey_GamepadR3) && enableFrameStep && !init)
		frameStep = true;
	if (c.R3framestep && ImGui::IsKeyReleased(ImGuiKey_GamepadR3) && enableFrameStep && init)
		init = false;
	if (c.R3framestep && ImGui::IsKeyDown(ImGuiKey_GamepadR3) && enableFrameStep && framecount >= 0.5 * ImGui::GetIO().Framerate && !init) {
		enableFrameStep = false;
		framecount = 0;
	}
	if (c.R3framestep && ImGui::IsKeyPressed(ImGuiKey_GamepadR3, false) && !enableFrameStep) {
		enableFrameStep = true;
		init = true;
	}
	if (c.R3framestep && !ImGui::IsKeyDown(ImGuiKey_GamepadR3)) {
		framecount = 0;
	}
	framecount += 1.0f;
	
	
	cui.createMenu();
	cui.padMenu();
	cui.grabDuelInputs();
	
	gs.createMenu();
	r.createMenu();
	ro.createMenu();
	c.createMenu();
	m.createMenu();
	globals::modConsole->render();
	
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
		if (ImGui::MenuItem("Input Display", "")) { cui.toggleMenu(); }
		if (ImGui::MenuItem("Player Control", "")) { NULL; }
		if (ImGui::MenuItem("Customize Controls", "")) { NULL; }
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Other"))
	{
		if (ImGui::MenuItem("Roster", "")) { ro.toggleMenu(); }
		if (ImGui::MenuItem("Message", "")) { m.toggleMenu(); }
		ImGui::EndMenu();
	}
	ImGui::EndMainMenuBar();
}