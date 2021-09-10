#include "pch.hpp"

#include "Core/Hooks/Hooks.hpp"
#include "Core/ModConsole/ModConsole.hpp"

#include "imgui/include/imgui_impl_dx11.h"
#include "imgui/include/imgui_impl_win32.h"
#include "sdl2/include/SDL.h"
#include "sdl2/include/SDL_keyboard.h"

#include "stb_image.h"
static ID3D11RenderTargetView* g_RenderTargetView;

static bool showWindow = true;
namespace hooks {
	LRESULT __stdcall functions::hkPresent(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags) {
		static std::once_flag init;

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
			io.Fonts->AddFontFromFileTTF("fonts.ttf", 13);
		});



		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();

		ImGui::NewFrame();
		ImGui::SetNextWindowSize({400, 400}, ImGuiCond_FirstUseEver);

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



// Simple helper function to load an image into a DX11 texture with common settings
bool LoadTextureFromFile(const char* filename, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height)
{
	// Load from disk into a raw RGBA buffer
	int image_width = 0;
	int image_height = 0;
	unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
	if (image_data == NULL)
		return false;

	// Create texture
	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Width = image_width;
	desc.Height = image_height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;

	ID3D11Texture2D* pTexture = NULL;
	D3D11_SUBRESOURCE_DATA subResource;
	subResource.pSysMem = image_data;
	subResource.SysMemPitch = desc.Width * 4;
	subResource.SysMemSlicePitch = 0;
	g_pd3dDevice->CreateTexture2D(&desc, &subResource, &pTexture);

	// Create texture view
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = desc.MipLevels;
	srvDesc.Texture2D.MostDetailedMip = 0;
	g_pd3dDevice->CreateShaderResourceView(pTexture, &srvDesc, out_srv);
	pTexture->Release();

	*out_width = image_width;
	*out_height = image_height;
	stbi_image_free(image_data);

	return true;
}