#include "pch.hpp"

#include "Core/Hooks/Hooks.hpp"

#include "imgui/include/imgui_impl_dx11.h"
#include "imgui/include/imgui_impl_win32.h"

#include "Core/Engine/engine.hpp"
#include "Rendering/render.hpp"

#include "Core/Gamepad/gamepad.hpp"
#include "Core/Online/online.hpp"
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
			io.Fonts->AddFontFromFileTTF(".\\s1api\\font\\FOT-Reggae Std B.ttf",30);//gameSettings::xRes/48);
			io.IniFilename = NULL;
			ImGui_ImplWin32_Init(sdk::game::gameWindow);
			ImGui_ImplDX11_Init(sdk::game::device, sdk::game::deviceContext);

			globals::modConsole->buildCommands();
		});

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();

		ImGui::NewFrame();
		ImGuiWindowFlags window_flags = 0;
		ImGui::GetIO().WantCaptureKeyboard = 1;
		window_flags |= ImGuiWindowFlags_NoResize;
		window_flags |= ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoScrollbar;
		window_flags |= ImGuiWindowFlags_NoScrollWithMouse;
		ImGui::GetStyle().WindowMenuButtonPosition = ImGuiDir_None;
		ImGui::SetNextWindowSize({960, 540});
		ImGui::SetNextWindowPos({ 0,0 });
		ImGui::GetStyle().WindowRounding = 0.0f;
		ImGui::Begin("Online Mode", NULL, window_flags);
		if (ImGui::BeginTabBar("tabs")) {
			if (ImGui::BeginTabItem("Host Game")) {
				ImGui::InputText("input text", str0, sizeof(str0));
				ImGui::SliderInt("Frame Delay", &S1API::framedelay, 1, 10);
				ImGui::Button("Start Host");
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Join Game")) {
				ImGui::Button("Join Game");
				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		}
		//globals::modConsole->render();
		//ImGui::Text("Hello, world %d", 123);
		/*
		if ((GetAsyncKeyState(VK_ESCAPE) & 0x01)) {
			printf_s("shit\n");
			if (render::uiOn)
				render::uiOn = 0;
			else
				render::uiOn = 1;
		}*/
		
		ImGui::EndFrame();
		ImGui::Render();

		sdk::game::deviceContext->OMSetRenderTargets(1, &g_RenderTargetView, nullptr);

		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		return globals::hookManager->callOriginal<decltype(&hkPresent)>(hkPresent, swapChain, syncInterval, flags);
	}
}