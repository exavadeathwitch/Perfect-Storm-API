#include "pch.hpp"

#include "Core/Hooks/Hooks.hpp"
#include "Core/ModConsole/ModConsole.hpp"

#include "imgui/include/imgui_impl_dx11.h"
#include "imgui/include/imgui_impl_win32.h"

#include "Textures/Textures.hpp"

#include "Util/Display/Display.hpp"

#include "GameSettings/gameSettings.hpp"

#include "Net/net.hpp"

#include "Battle/battle.hpp"

#include "Core/Settings/Settings.hpp"

#include <iostream>
bool once = 0;
static ID3D11RenderTargetView* g_RenderTargetView;

int my_image_width = 0;
int my_image_height = 0;
ID3D11ShaderResourceView* my_texture = NULL;

static bool showWindow = true;
namespace hooks {
	LRESULT __stdcall functions::hkPresent(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags) {
		static std::once_flag init;
		gameSettings::functions::updateSettings();
		if (showWindow)
			ShowCursor(true);
		else
			ShowCursor(false);

		std::call_once(init, [&swapChain]() {
			ID3D11Texture2D* backBuffer{};
			swapChain->GetDevice(__uuidof(ID3D11Device), std::bit_cast<void**>(&sdk::game::device));
			sdk::game::device->GetImmediateContext(&sdk::game::deviceContext);
			swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);
			sdk::game::device->CreateRenderTargetView(backBuffer, nullptr, &g_RenderTargetView);
			backBuffer->Release();

			ImGui::CreateContext();

			ImGui_ImplWin32_Init(sdk::game::gameWindow);
			ImGui_ImplDX11_Init(sdk::game::device, sdk::game::deviceContext);

			globals::modConsole->buildCommands();

			ImGuiIO& io = ImGui::GetIO();
			io.Fonts->AddFontFromFileTTF("fonts.ttf", gameSettings::xRes / 40);//gameSettings::xRes/48);
			io.IniFilename = NULL;
																			   /*
			bool ret = util::display::load::loadTextureFromFile("MyImage01.jpg", &my_texture, &my_image_width, &my_image_height);
			IM_ASSERT(ret);
			*/
			freopen("conin$", "r", stdin);
			freopen("conout$", "w", stdout);
			freopen("conout$", "w", stderr);
			});



		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();

		ImGui::NewFrame();

		if (Battle::inBattle && Net::functions::onOnline) {
			
			ImGuiWindowFlags window_flags = 0;
			window_flags |= ImGuiWindowFlags_NoBackground;
			window_flags |= ImGuiWindowFlags_NoTitleBar;
			window_flags |= ImGuiWindowFlags_NoResize;
			window_flags |= ImGuiWindowFlags_NoScrollbar;
			window_flags |= ImGuiWindowFlags_NoScrollWithMouse;

			if (globals::settings->m_frameDelayPosition == 0) 
				ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f), 0, ImVec2(0.0f, 0.0f));
			else 
				ImGui::SetNextWindowPos(ImVec2(.915f * (gameSettings::xRes / 2), 0.0f), 0, ImVec2(0.0f, 0.0f));

			ImGui::Begin("", NULL, window_flags);
			if (Net::frameDelay < 10)
				ImGui::Text("Delay: %d", Net::frameDelay);
			if (Net::frameDelay >= 10)
				ImGui::Text("Delay: %d*", Net::frameDelay);

			ImGui::End();
			//ImGui::Image((void*)my_texture, ImVec2(my_image_width, my_image_height));

			}

		if (console::enabled)
			globals::modConsole->render();

		if ((GetAsyncKeyState(VK_ESCAPE) & 0x01)) {
			if (console::enabled)
				console::enabled = 0;
			else
				console::enabled = 1;
		}

		ImGui::EndFrame();
		ImGui::Render();
		sdk::game::deviceContext->OMSetRenderTargets(1, &g_RenderTargetView, nullptr);

		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		return globals::hookManager->callOriginal<decltype(&hkPresent)>(hkPresent, swapChain, syncInterval, flags);
	}
}


