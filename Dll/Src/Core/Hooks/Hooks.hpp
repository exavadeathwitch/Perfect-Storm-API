#pragma once

#include <d3d11.h>
#include <dxgi.h>

namespace hooks {
	void initialize() noexcept;
	void uninitialize() noexcept;

	inline WNDPROC ogWndProc = nullptr;

	namespace functions {
		LRESULT __stdcall hkPresent(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags);
		LRESULT __stdcall hkWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	}
}
