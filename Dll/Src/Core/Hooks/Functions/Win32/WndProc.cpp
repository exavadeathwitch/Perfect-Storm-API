#pragma once

#include "pch.hpp"

#include "Core/Hooks/Hooks.hpp"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace hooks {
	LRESULT __stdcall functions::hkWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam))
			return TRUE;

		return CallWindowProcA(ogWndProc, hwnd, msg, wParam, lParam);
	}
}
