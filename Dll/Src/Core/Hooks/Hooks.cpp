#include "pch.hpp"

#include "Hooks.hpp"

#include "Core/Globals.hpp"

#include "Player/Mechanics/mech.hpp"

#include "Net/net.hpp"

#include "Battle/battle.hpp"
namespace hooks {
	void initialize() noexcept {
		globals::hookManager->initialize();

		globals::hookManager->addEntry(sdk::game::swapChainVtbl[8], functions::hkPresent);
		
		globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0x7ADCB4 + 0xC00), mechanics::functions::newPlayerState);
		
		globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0x7AD024 + 0xC00), mechanics::functions::canYouShuriken);
		
		globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0x22A208 + 0xC00), mechanics::functions::setNoChakraCirclePlayerState);

		globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0x77D8A0 + 0xC00), mechanics::functions::newPlayerAnim);

		globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0x7DF614 + 0xC00), mechanics::functions::setMultiInputPlayerState);

		globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0x7E09F4 + 0xC00), mechanics::functions::itemState);

		globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0x7AD960 + 0xC00), mechanics::functions::areYouComboing);

		globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0x7920CC + 0xC00), mechanics::functions::movementChain);

		globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0x7AFA38 + 0xC00), mechanics::functions::cdashState);

		globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0x7AFBC8 + 0xC00), mechanics::functions::backACD);

		globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0x79BD44 + 0xC00), mechanics::functions::setDashPriority);

		globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0x7E5C2C + 0xC00), mechanics::functions::writeSupportState);

		globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0x5763A0 + 0xC00), mechanics::functions::writeSwitchByte);
		
		globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0x78138C + 0xC00), mechanics::functions::comboGuardBreak);

		globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0xAEF4F0 + 0xC00), Net::functions::calculateFrame);

		globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0xAF29E0 + 0xC00), Net::functions::randomNet);

		globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0xAEF2A0 + 0xC00), Net::functions::sub_140AEFEA0);

		globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0x74C648 + 0xC00), Battle::functions::matchCount);
		
		globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0x70C478 + 0xC00), Battle::functions::battleEnd);

		globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0x6E1310 + 0xC00), Battle::functions::loadDisconnectPopUp);
		
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
