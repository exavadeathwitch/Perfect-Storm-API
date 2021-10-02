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

#include "Input/Input.hpp"

#include "Core/Settings/Settings.hpp"

#include "Net/Online Training/oTraining.hpp"

#include "Util/Memory/Modify.hpp"

#include "Player/Mechanics/mech.hpp"

#include <iostream>
bool movesetToggle = 0;
bool trainingModeIcon = 0;
bool trainingModeIcon2 = 0;
int trainingModeIconH = 0;
int trainingModeIconW = 0;
int trainingModeIcon2H = 0;
int trainingModeIcon2W = 0;
ID3D11ShaderResourceView* my_texture = NULL;
ID3D11ShaderResourceView* dtrainingModeIcon = NULL;
ID3D11ShaderResourceView* dtrainingModeIcon2 = NULL;
static ID3D11RenderTargetView* g_RenderTargetView;

int framecount = 0;
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
																			   
			bool ret = util::display::load::loadTextureFromFile("On.png", &dtrainingModeIcon, &trainingModeIconW, &trainingModeIconH);
			IM_ASSERT(ret);
			ret = util::display::load::loadTextureFromFile("Off.png", &dtrainingModeIcon2, &trainingModeIcon2W, &trainingModeIcon2H);
			IM_ASSERT(ret);
			
			freopen("conin$", "r", stdin);
			freopen("conout$", "w", stdout);
			freopen("conout$", "w", stderr);
			});
		if (framecount > 0)
		framecount--;

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();

		ImGui::NewFrame();


		if ((GetAsyncKeyState(VK_ESCAPE) & 0x01)) {
			if (console::enabled)
				console::enabled = 0;
			else
				console::enabled = 1;
		}	
		if ((GetAsyncKeyState(VK_TAB) & 0x01)) {
			if (movesetToggle)
				movesetToggle = 0;
			else
				movesetToggle = 1;
		}
		if (movesetToggle = 1) {
			ImGui::Begin("Moveset Toggles");
			ImGui::Checkbox("NM Tilt", &mechanics::enableNMTilt);
			ImGui::Checkbox("GKunai Air Combo", &mechanics::enableGKunaiAirCombo);
			ImGui::Checkbox("NM Tilt", &mechanics::enableNMTilt);
			ImGui::Checkbox("GKunai Air Combo", &mechanics::enableGKunaiAirCombo);
		
		}
		if (framecount == 0) {
			if (Input::functions::getMenuInput() == 1) {
				if (trainingModeIcon2) {
					trainingModeIcon2 = 0;
					framecount = 5;
				}
				else {
					trainingModeIcon2 = 1;
					framecount = 5;
				}
			}
		}
		//std::cout << trainingModeIcon2 << std::endl;
		if (trainingModeIcon2) {

			ImGuiWindowFlags window_flags = 0;
			window_flags |= ImGuiWindowFlags_NoBackground;
			window_flags |= ImGuiWindowFlags_NoTitleBar;
			window_flags |= ImGuiWindowFlags_NoResize;
			window_flags |= ImGuiWindowFlags_NoScrollbar;
			window_flags |= ImGuiWindowFlags_NoScrollWithMouse;

				ImGui::SetNextWindowPos(ImVec2(100.0f, 100.0f), 0, ImVec2(0.5f, 0.5f));
			

			ImGui::Begin("", NULL, window_flags);

			ImGui::Image((void*)dtrainingModeIcon2, ImVec2(trainingModeIcon2W / (gameSettings::xRes / 150), trainingModeIcon2H / (gameSettings::xRes / 150)));
			ImGui::End();

		}
		//if (trainingModeIcon) {

			ImGuiWindowFlags window_flags = 0;
			window_flags |= ImGuiWindowFlags_NoBackground;
			window_flags |= ImGuiWindowFlags_NoTitleBar;
			window_flags |= ImGuiWindowFlags_NoResize;
			window_flags |= ImGuiWindowFlags_NoScrollbar;
			window_flags |= ImGuiWindowFlags_NoScrollWithMouse;

			ImGui::SetNextWindowPos(ImVec2(100.0f, 100.0f), 0, ImVec2(0.5f, 0.5f));


			ImGui::Begin("", NULL, window_flags);

			ImGui::Image((void*)dtrainingModeIcon, ImVec2(trainingModeIconW / (gameSettings::xRes / 150), trainingModeIconH / (gameSettings::xRes / 150)));
			ImGui::End();

		//}
		if (Battle::inBattle && Net::functions::onOnline()) {
			if (Battle::onlineTraining)
				OTraining::functions::enableOnlineTraining();

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

			//globals::modConsole->render();
		
		/*
		uintptr_t P1analogAddr = basecontrollerAddr + 0x2A;
		uintptr_t P1ButtonAddr = basecontrollerAddr + 0x29;
		uintptr_t P2analogAddr = basecontrollerAddr + 0x56;
		uintptr_t P2ButtonAddr = basecontrollerAddr + 0x55;
		*/
		ImGui::EndFrame();
		ImGui::Render();
		sdk::game::deviceContext->OMSetRenderTargets(1, &g_RenderTargetView, nullptr);

		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		return globals::hookManager->callOriginal<decltype(&hkPresent)>(hkPresent, swapChain, syncInterval, flags);
	}
}


