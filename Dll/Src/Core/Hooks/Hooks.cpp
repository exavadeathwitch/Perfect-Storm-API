#include "pch.hpp"

#include "Hooks.hpp"

namespace hooks {
	void initialize() noexcept {
		globals::hookManager->initialize();

		globals::hookManager->addEntry(sdk::game::swapChainVtbl[8], functions::hkPresent);

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