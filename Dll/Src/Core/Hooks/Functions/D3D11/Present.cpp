#include "pch.hpp"

#include "Core/Hooks/Hooks.hpp"

#include "imgui/include/imgui_impl_dx11.h"
#include "imgui/include/imgui_impl_win32.h"

#include "Core/DebugMenu/DebugMenu.hpp"

#include "sdl2/include/SDL.h"

#include "Core/DebugMenu/DebugTitle/DebugTitle.hpp"

#include "Util/Util.hpp"

#include "Util/Console/Console.hpp"
int resize = 1;
signed typedef int(__fastcall* loadCpk) ();
loadCpk oloadCpk = (loadCpk)(globals::moduleBase + 0x854F3C + 0xC00);
ID3D11RenderTargetView* g_RenderTargetView;
bool show_app_main_menu_bar;
namespace hooks {
	HRESULT __stdcall hooks::functions::hkResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
	{
		if (g_RenderTargetView) {
			sdk::game::deviceContext->OMSetRenderTargets(0, 0, 0);
			g_RenderTargetView->Release();
		}
		printf_s("hkresize\n");
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
				ImGuiIO& io = ImGui::GetIO();
				io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
				//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
				io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
				//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
				ImGui_ImplWin32_Init(sdk::game::gameWindow);
				ImGui_ImplDX11_Init(sdk::game::device, sdk::game::deviceContext);
				
				std::string path = util::getModPath().generic_string() + "\\ui\\font\\";
				std::replace(path.begin(), path.end(), '/', '\\');
				util::console::debugPrint(path + "\n");
				//io.Fonts->AddFontFromFileTTF((path + "FOT-Reggae Std B.ttf").c_str(), 14);
				for (const auto& file : std::filesystem::directory_iterator(path)) {
					if ((file.path().string()).ends_with(".ttf")) {
						int font_size = 14;
						std::string filenoend = file.path().string();
						filenoend = std::regex_replace(filenoend, std::regex(".ttf"), ".txt");
						std::ifstream f((filenoend).c_str());
						if (f.good()) {
							std::ifstream MyFile(filenoend);
							std::string output;
							getline(MyFile, output);
							font_size = std::stoi(output);
							MyFile.close();
						}
						io.Fonts->AddFontFromFileTTF(file.path().string().c_str(), font_size, NULL, io.Fonts->GetGlyphRangesJapanese());
					}
				}
					//io.Fonts->AddFontFromFileTTF(((entry.path()).generic_string()).c_str(), 13);
				//}
				//globals::modConsole->buildCommands();
				
				});
		}
		else
			return globals::hookManager->callOriginal<decltype(&hkPresent)>(hkPresent, swapChain, syncInterval, flags);


		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();

		ImGui::NewFrame();
		if (!runTitle) {
			DebugMenu::runDebugMenu();
		}
		DebugTitle::runDebugTitle();
		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		sdk::game::deviceContext->OMSetRenderTargets(1, &g_RenderTargetView, nullptr);


		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}
		return globals::hookManager->callOriginal<decltype(&hkPresent)>(hkPresent, swapChain, syncInterval, flags);
	}
}