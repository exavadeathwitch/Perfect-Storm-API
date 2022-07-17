#include "pch.hpp"

#include "Core/Hooks/Hooks.hpp"

#include "imgui/include/imgui_impl_dx11.h"
#include "imgui/include/imgui_impl_win32.h"
#include "imgui/include/imgui_stdlib.h"
#include "Core/Engine/engine.hpp"
#include "Rendering/render.hpp"
#include <string_view>
#include "Core/Gamepad/gamepad.hpp"
#include "Core/Online/online.hpp"
#include "base64mod/base64.h"
void reverseStr(std::string& str);
static ID3D11RenderTargetView* g_RenderTargetView;
char str0[128] = {};
namespace hooks {
	LRESULT __stdcall functions::hkPresent(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags) {
		static bool showWindow = true;
		static std::once_flag init;

		if (showWindow)
			ShowCursor(true);

		std::call_once(init, [&swapChain]() {
			ID3D11Texture2D* backBuffer{};
			swapChain->GetDevice(__uuidof(ID3D11Device), std::bit_cast<void**>(&sdk::game::device));
			sdk::game::device->GetImmediateContext(&sdk::game::deviceContext);
			swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);
			sdk::game::device->CreateRenderTargetView(backBuffer, nullptr, &g_RenderTargetView);
			backBuffer->Release();

			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO();
			io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
			//io.BackendFlags |= ImGuiBackendFlags_HasGamepad;
			io.Fonts->AddFontFromFileTTF(".\\s1api\\font\\FOT-Reggae Std B.ttf", 30);//gameSettings::xRes/48);
			io.IniFilename = NULL;
			ImGui_ImplWin32_Init(sdk::game::gameWindow);
			ImGui_ImplDX11_Init(sdk::game::device, sdk::game::deviceContext);

			globals::modConsole->buildCommands();
			});

		ImGuiIO& io = ImGui::GetIO();
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		if (S1API::onlinemenu) {
			ImGuiWindowFlags window_flags = 0;
			ImGui::GetIO().WantCaptureKeyboard = 1;
			window_flags |= ImGuiWindowFlags_NoResize;
			window_flags |= ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoScrollbar;
			window_flags |= ImGuiWindowFlags_NoScrollWithMouse;
			ImGui::GetStyle().WindowMenuButtonPosition = ImGuiDir_None;
			ImGui::SetNextWindowSize({ 960, 540 });
			ImGui::SetNextWindowPos({ 0,0 });
			ImGui::GetStyle().WindowRounding = 0.0f;
			if (S1API::onlinemenu == 1) {
				ImGui::Begin("Online Mode", NULL, window_flags);
				if (ImGui::BeginTabBar("tabs")) {
					{
						if (ImGui::BeginTabItem("Host")) {
							ImGui::SliderInt("Frame Delay", &S1API::framedelay, 1, 10);
							ImGuistd::InputText("Host Port", &S1API::hostport);
							if (ImGui::Button("Create Session")) {
								S1API::hosting = 1;
								S1API::onlinemenu = 2;
							}
							ImGui::EndTabItem();
						}
						if (ImGui::BeginTabItem("Join")) {
							ImGuistd::InputText("IP Address", &S1API::iphost);
							ImGuistd::InputText("Port", &S1API::hostport);
							if (ImGui::Button("Join Session"))
								S1API::onlinemenu = 3;
							ImGui::EndTabItem();
						}
						if (ImGui::BeginTabItem("Quit")) {
							if (ImGui::Button("Back to Main Menu")) {
								S1API::onlinemenu = 0;
								engine::triggerMenu = 1;
							}
							ImGui::EndTabItem();
						}
						ImGui::EndTabBar();
					}
				}
			}
			if (S1API::onlinemenu == 2) {
				ImGui::Begin("Hosting Game", NULL, window_flags);
				S1API::iphost = S1API::getip();
				ImGui::Text("Join Code: ");
				ImGui::SameLine();
				ImGui::Text(&S1API::iphost[0]);
				ImGui::SameLine();
				if (ImGui::Button("Copy to Clipboard"))
					ImGui::SetClipboardText(&S1API::iphost[0]);
				ImGui::Text("Frame Delay: ");
				ImGui::SameLine();
				std::string framedelay = std::to_string(S1API::framedelay);
				ImGui::Text(&framedelay[0]);
				if (ImGui::Button("Leave Session")) {
					S1API::onlinemenu = 1;
					S1API::iphost = "";
					S1API::hostport = "";
				}
			}
			if (S1API::onlinemenu == 3) {
				ImGui::Begin("Joining Session", NULL, window_flags);
				if (ImGui::Button("Cancel"))
					S1API::onlinemenu = 1;
			}

			if (S1API::onlinemenu == 4) {
				ImGui::Begin("Leave Session", NULL, window_flags);
				if (ImGui::Button("Yes")) {
					S1API::onlinemenu = 0;
					engine::triggerMenu = 1;
					ImGui::SameLine();
					if (ImGui::Button("No")) {
						S1API::onlinemenu = 0;

					}
				}
			}
			if (S1API::onlinemenu == 5) {
				ImGui::Begin("Leave Session", NULL, window_flags);
				if (ImGui::Button("Yes")) {
					S1API::onlinemenu = 0;
					engine::triggerMenu = 1;
					ImGui::SameLine();
					if (ImGui::Button("No")) {
						S1API::onlinemenu = 0;

					}
				}
			}

				//globals::modConsole->render();
				//ImGui::Text("Hello, world %d", 123);

				if ((GetAsyncKeyState(VK_SPACE) & 0x01)) {
					if (engine::triggerMenu)
						engine::triggerMenu = 0;
					else
						engine::triggerMenu = 1;
				}
			}
		
			ImGui::EndFrame();
			ImGui::Render();

			sdk::game::deviceContext->OMSetRenderTargets(1, &g_RenderTargetView, nullptr);

			ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

			return globals::hookManager->callOriginal<decltype(&hkPresent)>(hkPresent, swapChain, syncInterval, flags);
		
	}
	}
void reverseStr(std::string& str)
{
	int len = str.length();
	int n = len - 1;
	int i = 0;
	while (i <= n) {
		//Using the swap method to switch values at each index
		std::swap(str[i], str[n]);
		n = n - 1;
		i = i + 1;
	}

}