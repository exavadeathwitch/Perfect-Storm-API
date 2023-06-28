#pragma once

#include <dxgi.h>
#include <d3d11.h>

namespace sdk::game {

	bool initialize() noexcept;
	bool initializeGameWindow() noexcept;

	inline std::uintptr_t* swapChainVtbl = nullptr;
	inline ID3D11Device* device = nullptr;
	inline ID3D11DeviceContext* deviceContext = nullptr;
	inline HWND gameWindow = nullptr;
}
