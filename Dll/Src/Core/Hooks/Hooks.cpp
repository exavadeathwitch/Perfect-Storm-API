#include "pch.hpp"

#include "Hooks.hpp"

#include "Util/Memory/Modify.hpp"

#include "Rendering/render.hpp"

#include "Core/Engine/engine.hpp"
namespace hooks {
	void initialize() noexcept {
		globals::hookManager->initialize();

		globals::hookManager->addEntry(sdk::game::swapChainVtbl[8], functions::hkPresent);

		globals::hookManager->addEntry(globals::moduleBase + 0x54FB10 + 0xC00, render::Render::renderElements);

		//globals::hookManager->addEntry(globals::moduleBase + 0x24E698 + 0xC00, engine::Engine::pauseState);

		//globals::hookManager->addEntry(globals::moduleBase + 0x264200 + 0xC00, engine::Engine::gamelogic);

		globals::hookManager->hookAllEntries();

		ogWndProc = std::bit_cast<WNDPROC>(GetWindowLongPtrA(sdk::game::gameWindow, GWLP_WNDPROC));

		SetWindowLongPtrA(sdk::game::gameWindow, GWLP_WNDPROC, std::bit_cast<LONG_PTR>(&functions::hkWndProc));
	}

	void uninitialize() noexcept {
		SetWindowLongPtrA(sdk::game::gameWindow, GWLP_WNDPROC, std::bit_cast<LONG_PTR>(ogWndProc));

		globals::hookManager->unhookAllEntries();
		globals::hookManager->uninitialize();
	}
}