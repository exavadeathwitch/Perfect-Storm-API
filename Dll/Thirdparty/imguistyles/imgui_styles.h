#pragma once

#include "imgui/include/imgui.h"
#include "imgui/include/imgui_internal.h"

namespace ImGui {
	IMGUI_API void LoadStyleFrom(const char* fileName);
	IMGUI_API void SaveStylesTo(const char* fileName);
}
