#include "pch.hpp"

#include "Core/Hooks/Hooks.hpp"
#include "Core/ModConsole/ModConsole.hpp"

#include "imgui/include/imgui_impl_dx11.h"
#include "imgui/include/imgui_impl_win32.h"

#include "Textures/Textures.hpp"

#include "Scene/gamemodeselect/gms.hpp"

#include "General/general.hpp"

#include "Util/Display/Display.hpp"

#include "GameSettings/gameSettings.hpp"

#include "Net/net.hpp"

#include "Battle/battle.hpp"

#include "Input/gInput.hpp"

#include "Core/Settings/Settings.hpp"

#include "Net/Online Training/oTraining.hpp"

#include "Util/Memory/Modify.hpp"

#include "Player/Mechanics/mech.hpp"

#include "Util/Sound/Music.hpp"

#include "Util/Sound/SDL2Music.h"

#include <iostream>
int framecount = 0;
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
int thing = 0;
static bool showWindow = true;
namespace hooks {
	LRESULT __stdcall functions::hkPresent(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags) {
		static const auto retval = globals::hookManager->callOriginal<decltype(&hkPresent)>(hkPresent, swapChain, syncInterval, flags);
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
			//return retval;
			swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);
			sdk::game::device->CreateRenderTargetView(backBuffer, nullptr, &g_RenderTargetView);
			backBuffer->Release();
			ImGui::CreateContext();

			ImGui_ImplWin32_Init(sdk::game::gameWindow);
			ImGui_ImplDX11_Init(sdk::game::device, sdk::game::deviceContext);

			globals::modConsole->buildCommands();

			ImGuiIO& io = ImGui::GetIO();
			io.Fonts->AddFontFromFileTTF(".\\Perfect Storm\\ui\\font\\FOT-Reggae Std B.ttf", gameSettings::xRes / 40);//gameSettings::xRes/48);
			io.IniFilename = NULL;

			//Texture Loading Goes Here
				/*
			bool ret = util::display::load::loadTextureFromFile("On.png", &dtrainingModeIcon, &trainingModeIconW, &trainingModeIconH);
			IM_ASSERT(ret);
			ret = util::display::load::loadTextureFromFile("Off.png", &dtrainingModeIcon2, &trainingModeIcon2W, &trainingModeIcon2H);
			IM_ASSERT(ret);
			*/
			});
		if (framecount > 0)
		framecount--;

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		*(DWORD*)(globals::moduleBase + 0x163BBD0) = 1;
		ImGui::NewFrame();
		/*
		if ((GetAsyncKeyState(VK_TAB) & 0x01)) {
			if (movesetToggle)
				movesetToggle = 0;
			else
				movesetToggle = 1;
		}
		*/
		if (movesetToggle == 1) {
			ImGui::Begin("Moveset Toggles");
			ImGui::Checkbox("NM Tilt", &mechanics::enableNMTilt);
			ImGui::Checkbox("GKunai Air Combo", &mechanics::enableGKunaiAirCombo);
			ImGui::Checkbox("Ninja Move Grab", &mechanics::enableNMGrab);
			ImGui::Checkbox("Enable GKunai", &mechanics::enableGKunai);
			ImGui::Checkbox("Enable Shuriken From Combo/Tilt", &mechanics::enableShurikenComboTilt);
			ImGui::Checkbox("Enable Tilt Cancels", &mechanics::enableTiltCancels);
			ImGui::Checkbox("Enable Full Combo Switch", &mechanics::enableFullComboSwitch);
			ImGui::Checkbox("Enable Fast Air Chakra Dash", &mechanics::enableFastACD);
			ImGui::Checkbox("Air Back Chakra Dash Spark", &mechanics::enableABCDSpark);
			ImGui::Checkbox("Back Chakra Dash Priority", &mechanics::enableDashPriority);
			ImGui::Checkbox("Rev Ninja Move", &mechanics::enableRevNM);
			ImGui::Checkbox("Rev Ninja Move Kunai", &mechanics::enableRevNMK);
			ImGui::Checkbox("Cover Fire Chakra Shuriken", &mechanics::enableCFCS);
			ImGui::Checkbox("Guard to Item", &mechanics::enableGTI);
			ImGui::Checkbox("Tilt Switch", &mechanics::enableTiltSwitch);
			ImGui::Checkbox("Grab Switch", &mechanics::enableGrabSwitch);
			ImGui::Checkbox("Shuriken Switch", &mechanics::enableShurikenSwitch);
			ImGui::Checkbox("Chakra Shuriken Switch", &mechanics::enableChakraShurikenSwitch);
		}
		/*
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
		*/
		//std::cout << trainingModeIcon2 << std::endl;

		Mix_VolumeMusic(gameSettings::musicVol / 1.25);
		if (General::musicaddr != NULL) {
			if (General::musictrack == 0 && *(float*)(General::musicaddr + 0xD8 + 0x6C) == 1.0f)
				music::introtrack = 1;
			if (General::musictrack == 2 && General::prevtrack == 0)
				music::introtrack = 2;
		}
		gms::gamefunc = 0;
		if (trainingModeIcon2) {

			ImGuiWindowFlags window_flags = 0;
			window_flags |= ImGuiWindowFlags_NoBackground;
			window_flags |= ImGuiWindowFlags_NoTitleBar;
			window_flags |= ImGuiWindowFlags_NoResize;
			window_flags |= ImGuiWindowFlags_NoScrollbar;
			window_flags |= ImGuiWindowFlags_NoScrollWithMouse;
			

			ImGui::Begin("", NULL, window_flags);

			ImGui::Image((void*)dtrainingModeIcon2, ImVec2(trainingModeIcon2W / (gameSettings::xRes / 150), trainingModeIcon2H / (gameSettings::xRes / 150)));
			ImGui::End();

		}
		//if (trainingModeIcon) {
		/*
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
			*/
	//}

		*(DWORD*)(globals::moduleBase + 0x163BBD0) = 1;
		if (Battle::inBattle && Net::functions::onOnline()) {
			//if (globals::settings->m_frameDelayPosition == true)
			
			if (globals::settings->m_enableTraining) {
				if ((GetAsyncKeyState(VK_ESCAPE) & 0x01)) {
					if (console::enabled)
						console::enabled = 0;
					else
						console::enabled = 1;
				}
				if (console::enabled)
				OTraining::functions::enableOnlineTraining();
			}
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
		Battle::inBattle = 0;
		//std::cout << "thing: " << thing << std::endl;
		//thing++;
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		return globals::hookManager->callOriginal<decltype(&hkPresent)>(hkPresent, swapChain, syncInterval, flags);
	}
}


