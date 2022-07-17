#include "pch.hpp"

#include "Hooks.hpp"

#include "Util/Memory/Modify.hpp"

#include "Rendering/render.hpp"

#include "Core/Engine/engine.hpp"

#include "Core/Gamepad/gamepad.hpp"
namespace hooks {
	void initialize() noexcept {
		globals::hookManager->initialize();

		globals::hookManager->addEntry(sdk::game::swapChainVtbl[8], functions::hkPresent);

		globals::hookManager->addEntry(globals::moduleBase + 0x54FB10 + 0xC00, render::Render::renderElements);

		//globals::hookManager->addEntry(globals::moduleBase + 0x138A40 + 0xC00, S1API::gamepad::gamepadLoop);

		globals::hookManager->addEntry(globals::moduleBase + 0x48C690 + 0xC00, S1API::gamepad::getPadAddr);

		globals::hookManager->addEntry(globals::moduleBase + 0x398EF4 + 0xC00, engine::Engine::enableWindow);

		globals::hookManager->addEntry(globals::moduleBase + 0x2636A0 + 0xC00, engine::Engine::battleStart);

		globals::hookManager->addEntry(globals::moduleBase + 0x17F67C + 0xC00, engine::Engine::initStuff);

		globals::hookManager->addEntry(globals::moduleBase + 0x43B230 + 0xC00, engine::Engine::outBattle);
		//
		globals::hookManager->addEntry(globals::moduleBase + 0x24FA40 + 0xC00, engine::Engine::ccGameManager_Play);

		//globals::hookManager->addEntry(globals::moduleBase + 0x3A8534 + 0xC00, engine::Engine::MainProcess);
		
		globals::hookManager->addEntry(globals::moduleBase + 0x265684 + 0xC00, engine::Engine::resultsignal);

		globals::hookManager->addEntry(globals::moduleBase + 0x2660B8 + 0xC00, engine::Engine::withoutwin);
		
		globals::hookManager->addEntry(globals::moduleBase + 0x264068 + 0xC00, engine::Engine::gameduelmain);

		globals::hookManager->addEntry(globals::moduleBase + 0x24F38C + 0xC00, engine::Engine::LoadExpectedScene);

		globals::hookManager->addEntry(globals::moduleBase + 0x1D33D4 + 0xC00, engine::Engine::menuControl);

		globals::hookManager->addEntry(globals::moduleBase + 0x4CF270 + 0xC00, engine::Engine::loadText);
		
		globals::hookManager->addEntry(globals::moduleBase + 0x24E698 + 0xC00, engine::Engine::pauseState);

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