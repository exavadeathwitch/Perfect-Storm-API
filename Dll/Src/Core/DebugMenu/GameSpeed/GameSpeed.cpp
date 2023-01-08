#include "pch.hpp"

#include "GameSpeed.hpp"

#include "Game/cc/ccGameObject/ccGameObject.hpp"

#include "Game/ccTask/ccTask.hpp"

#include "imguiwidget/widget.hpp"

#include "Core/DebugMenu/MenuMessage/MenuMessage.hpp"
void GameSpeed::runMenu() {
	int prevgamespeed = gameSpeed;
	ImGui::SliderInt(speedSetting[gameSpeed], &gameSpeed, 0, 4, "", ImGuiSliderFlags_NoInput);
	if (prevgamespeed == 1 && prevgamespeed != gameSpeed)
		alternate = 1;
	ImGui::SameLine(); widget::HelpMarker(gamespeedmessageset.getMessage(0).getconverted().c_str());
	ImGui::Checkbox(gamespeedmessageset.getMessage(1).getconverted().c_str(), &enableFrameStep);
	ImGui::SameLine(); widget::HelpMarker(gamespeedmessageset.getMessage(2).getconverted().c_str());
	if (enableFrameStep) {
		ImGui::SliderInt(gamespeedmessageset.getMessage(3).getconverted().c_str(), &frameStepCount, 1, 10, "%d", ImGuiSliderFlags_NoInput);
		ImGui::SameLine(); widget::HelpMarker(gamespeedmessageset.getMessage(4).getconverted().c_str());
		if (ImGui::Button(((gamespeedmessageset.getMessage(5).getconverted() + " ").c_str() + std::to_string(frameStepCount) + (gamespeedmessageset.getMessage(6).getconverted() + " ").c_str()).c_str()))
			frameStep = true;
		ImGui::SameLine(); widget::HelpMarker(gamespeedmessageset.getMessage(7).getconverted().c_str());
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