#include "pch.hpp"

#include "Core/Hooks/Hooks.hpp"

#include "imgui/include/imgui_impl_dx11.h"
#include "imgui/include/imgui_impl_win32.h"

#include "Core/Globals.hpp"

#include "imguistyles/imgui_styles.h"

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

		if (showWindow)
			ShowCursor(true);
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
				std::ifstream f(util::getImguiStylePath());
				if (!f.good()) {
					ImGui::SaveStylesTo(util::getImguiStylePath().string().c_str());
				}
				ImGui::LoadStyleFrom(util::getImguiStylePath().string().c_str());
				//globals::modConsole->buildCommands();
				for (int x = 0; x < globals::modLoader.mods.size(); x++) {
					typedef void(__stdcall* funct)(uintptr_t* swapChainVtbl, ID3D11Device* device, ID3D11DeviceContext* deviceContext, HWND gameWindow);
					funct sdkPassthrough = (funct)GetProcAddress(globals::modLoader.mods[x].dll, "sdkPassthrough");
					switch (globals::modLoader.mods[x].type) {
					case 0:
						continue;
					case 1:
						if (sdkPassthrough)
							sdkPassthrough(sdk::game::swapChainVtbl, sdk::game::device, sdk::game::deviceContext, sdk::game::gameWindow);
						break;
					}
				}
				});
		}
		else
			return globals::hookManager->callOriginal<decltype(&hkPresent)>(hkPresent, swapChain, syncInterval, flags);


		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();

		ImGui::NewFrame();
		globals::modMenu.runMenu();
		for (int x = 0; x < globals::modLoader.mods.size(); x++) {
			typedef void(__stdcall* initfunctloop)(__int64 moduleBase);
			initfunctloop functloop = (initfunctloop)GetProcAddress(globals::modLoader.mods[x].dll, "GameLoop");
			typedef void(__stdcall* initfunctimguiloop)(__int64 moduleBase, ImGuiContext* context);
			initfunctimguiloop functimguiloop = (initfunctimguiloop)GetProcAddress(globals::modLoader.mods[x].dll, "modLoop");
			switch (globals::modLoader.mods[x].type) {
			case 0:
				if (functloop)
					functloop(globals::moduleBase);
				break;
			case 1:
				if (functimguiloop)
					functimguiloop(globals::moduleBase, ImGui::GetCurrentContext());
				break;
			}
		}

		ImGui::EndFrame();
		ImGui::Render();

		sdk::game::deviceContext->OMSetRenderTargets(1, &g_RenderTargetView, nullptr);

		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		return globals::hookManager->callOriginal<decltype(&hkPresent)>(hkPresent, swapChain, syncInterval, flags);
	}
}