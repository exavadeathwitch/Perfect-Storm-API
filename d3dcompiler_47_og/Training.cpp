#include "Training.h"
#include "imgui/imgui.h"
#include <iostream>
#include "includes.h"
#include "DX11 Initialize.h"
#include "CasualLibrary.hpp"
using namespace training;

void training::EnableOnlineTraining()
{
	if (TrainingisOn == true)
	{
		Address baseAddr = Memory::Internal::getModule("NSUNS4.exe");
		Address timerAddr = Memory::Internal::getAddress(baseAddr + 0x01609B88, { 0x1E8 });
		Memory::Internal::write<int>(timerAddr, -1, true);
		ImGui::Begin("Training Mode");
		ImGui::Text("Both players need to enable the same settings to avoid desyncs.");
		ImGui::Combo("Life", &selectedLItem, Litems, IM_ARRAYSIZE(Litems));
		ImGui::Checkbox("Unlimited Chakra", &tcheckBox[0]);
		ImGui::Checkbox("Unlimited Support", &tcheckBox[1]);
		ImGui::Checkbox("Unlimited Guard Health", &tcheckBox[2]);
		ImGui::Checkbox("Unlimited Substitution", &tcheckBox[3]);
		ImGui::Checkbox("Unlimited Ninja Tools", &tcheckBox[4]);
		ImGui::Combo("Storm Gauge", &selectedSGItem, SGitems, IM_ARRAYSIZE(SGitems));
	}
}