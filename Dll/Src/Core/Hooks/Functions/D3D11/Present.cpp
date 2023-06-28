#include "pch.hpp"

#include "Core/Hooks/Hooks.hpp"

#include "imgui/include/imgui_impl_dx11.h"
#include "imgui/include/imgui_impl_win32.h"

ID3D11RenderTargetView* g_RenderTargetView;

namespace hooks {
	HRESULT __stdcall hooks::functions::hkResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
	{
		if (g_RenderTargetView) {
			sdk::game::deviceContext->OMSetRenderTargets(0, 0, 0);
			g_RenderTargetView->Release();
		}

		HRESULT hr = globals::hookManager->callOriginal<decltype(&hkResizeBuffers)>(hkResizeBuffers, pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);

		ID3D11Texture2D* pBuffer;
		pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBuffer);
		// Perform error handling here!

		sdk::game::device->CreateRenderTargetView(pBuffer, NULL, &g_RenderTargetView);
		// Perform error handling here!
		pBuffer->Release();

		sdk::game::deviceContext->OMSetRenderTargets(1, &g_RenderTargetView, NULL);

		// Set up the viewport.
		D3D11_VIEWPORT vp;
		vp.Width = Width;
		vp.Height = Height;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		sdk::game::deviceContext->RSSetViewports(1, &vp);
		return hr;
	}
	LRESULT __stdcall functions::hkPresent(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags) {
		static bool showWindow = true;
		static std::once_flag init;

		//if (showWindow)
			//ShowCursor(true);
		if (SUCCEEDED(swapChain->GetDevice(__uuidof(ID3D11Device), (void**)&sdk::game::device)))
		{
			std::call_once(init, [&swapChain]() {
				sdk::game::device->GetImmediateContext(&sdk::game::deviceContext);
				DXGI_SWAP_CHAIN_DESC sd;
				swapChain->GetDesc(&sd);
				sdk::game::gameWindow = sd.OutputWindow;
				ID3D11Texture2D* pBackBuffer;
				swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
				sdk::game::device->CreateRenderTargetView(pBackBuffer, nullptr, &g_RenderTargetView);
				pBackBuffer->Release();
				ImGui::CreateContext();

				ImGui_ImplWin32_Init(sdk::game::gameWindow);
				ImGui_ImplDX11_Init(sdk::game::device, sdk::game::deviceContext);

				//globals::modConsole->buildCommands();
				});
		}
		else
			return globals::hookManager->callOriginal<decltype(&hkPresent)>(hkPresent, swapChain, syncInterval, flags);


		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();

		ImGui::NewFrame();
		//ImGui::Text("Hello, world %d", 123);
		//printf_s("shit\n");
		ImGui::SetNextWindowSize({400, 400}, ImGuiCond_FirstUseEver);
		//globals::modConsole->render();

		ImGui::EndFrame();
		ImGui::Render();

		sdk::game::deviceContext->OMSetRenderTargets(1, &g_RenderTargetView, nullptr);

		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		return globals::hookManager->callOriginal<decltype(&hkPresent)>(hkPresent, swapChain, syncInterval, flags);
	}
}