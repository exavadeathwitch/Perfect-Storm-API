#include "pch.hpp"

#include "GameSpeed.hpp"

#include "Game/cc/ccGameObject/ccGameObject.hpp"

#include "Game/ccTask/ccTask.hpp"

#include "imguiwidget/widget.hpp"

void GameSpeed::runMenu() {
	int prevgamespeed = gameSpeed;
	ImGui::SliderInt(speedSetting[gameSpeed], &gameSpeed, 0, 4, "", ImGuiSliderFlags_NoInput);
	if (prevgamespeed == 1 && prevgamespeed != gameSpeed)
		alternate = 1;
	ImGui::SameLine(); widget::HelpMarker("This slider controls the speed of the game. Does not speed up UI animations.");
	ImGui::Checkbox("Enable Frame Step", &enableFrameStep);
	ImGui::SameLine(); widget::HelpMarker("Checking this box will make the game freeze and enable frame by frame advancement.");
	if (enableFrameStep) {
		ImGui::SliderInt("Number of Frames", &frameStepCount, 1, 10, "%d", ImGuiSliderFlags_NoInput);
		ImGui::SameLine(); widget::HelpMarker("This slider controls the number of game frames that are advanced when the button below is pressed.");
		if (ImGui::Button(("Step " + std::to_string(frameStepCount) + " Frame").c_str()))
			frameStep = true;
		ImGui::SameLine(); widget::HelpMarker("Pressing this button will advance the game by the number of frames above.");
	}
	/*
	ImGui::Text("Tasks");
	for (int i = 0; i < sizeof(ccGameObjectarr2); i++) {
		bool orig = ccGameObjectarr2[i];
		ImGui::Checkbox(std::to_string(i).c_str(), &orig);
		ccGameObjectarr2[i] = orig;
	}
	ImGui::End();*/
}