#include "pch.hpp"

#include "oTraining.hpp"

#include "Util/Memory/Modify.hpp"

#include <iostream>

#include "imgui/include/imgui_impl_dx11.h"
#include "imgui/include/imgui_impl_win32.h"

void OTraining::functions::enableOnlineTraining() {

	util::memory::Modify::writePointer((std::uintptr_t)(globals::moduleBase + 0x0161C8C8), { 0x1E8 }, (DWORD)(-1));
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