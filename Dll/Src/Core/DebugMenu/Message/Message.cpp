#include "pch.hpp"

#include "Message.hpp"

#include "imguiwidget/widget.hpp"

#include "Core/DebugMenu/MenuMessage/MenuMessage.hpp"

#include "Game/cc/ccUi/ccUi.hpp"

#include "imguimisc/cpp/imgui_stdlib.h"

#include "Util/Memory/String.hpp"
std::string test;
void Message::runMenu() {
	ImGui::Checkbox(messagemessageset.getMessage(0).getconverted().c_str(), &showTranslatedGameMessages);
	ImGui::SameLine(); widget::HelpMarker(messagemessageset.getMessage(1).getconverted().c_str());
	if (ImGui::Checkbox(messagemessageset.getMessage(2).getconverted().c_str(), &showMenuGameMessages))
		translateAllSets();
	ImGui::SameLine(); widget::HelpMarker(messagemessageset.getMessage(3).getconverted().c_str());
	ImGui::InputText(" ", buffer, 500);
	ImGui::SameLine();
	if (ImGui::Button(messagemessageset.getMessage(4).getconverted().c_str()))
		strcpy(buffer, (char*)(ccUiGetMessage(__int64(&buffer))));
	ImGui::SameLine();
	widget::HelpMarker(messagemessageset.getMessage(5).getconverted().c_str());
}