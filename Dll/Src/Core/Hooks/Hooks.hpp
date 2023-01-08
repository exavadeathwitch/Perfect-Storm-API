#pragma once

#include <d3d11.h>
#include <dxgi.h>

namespace hooks {
	void initialize() noexcept;
	void uninitialize() noexcept;
	void hookImportant();
	inline WNDPROC ogWndProc = nullptr;

	namespace functions {
		HRESULT __stdcall hkResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);
		LRESULT __stdcall hkPresent(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags);
		LRESULT __stdcall hkWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	}
}
