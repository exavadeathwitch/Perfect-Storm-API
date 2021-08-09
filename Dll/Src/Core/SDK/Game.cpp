#include "pch.hpp"

#include "Game.hpp"

#pragma comment(lib, "d3d11.lib")

namespace sdk::game {
	bool setSwapChainVtbl() noexcept {
		IDXGISwapChain* swapChain{};
		ID3D11Device* device{};
		ID3D11DeviceContext* deviceContext{};

		D3D_FEATURE_LEVEL featureLevel{};
		const D3D_FEATURE_LEVEL featureLevels[] = {D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_11_0};
		DXGI_SWAP_CHAIN_DESC swapChainDesc{};

		swapChainDesc.BufferCount = 1;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferDesc.Height = 100;
		swapChainDesc.BufferDesc.Width = 100;
		swapChainDesc.BufferDesc.RefreshRate = {60, 1};
		swapChainDesc.OutputWindow = GetForegroundWindow();
		swapChainDesc.Windowed = TRUE;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;

		if (FAILED(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, featureLevels,
			1, D3D11_SDK_VERSION, &swapChainDesc, &swapChain, &device, &featureLevel, &deviceContext))) {
			printf_s("couldn't create device and swapchain\n");
			return false;
		}

		swapChainVtbl = *reinterpret_cast<std::uintptr_t**>(swapChain);

		swapChain->Release();
		device->Release();
		deviceContext->Release();

		return true;
	}

	bool initialize() noexcept {
		if (!setSwapChainVtbl())
			return false;

		gameWindow = FindWindowA(nullptr, "NSUNS4");

		if (!gameWindow)
			return false;

		return true;
	}
}