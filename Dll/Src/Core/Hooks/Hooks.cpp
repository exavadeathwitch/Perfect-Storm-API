#include "pch.hpp"

#include "Hooks.hpp"

#include "Core/Globals.hpp"

#include "Player/Mechanics/mech.hpp"

#include "Net/net.hpp"

#include "Battle/battle.hpp"

#include "Player/Properties/prop.hpp"

#include "Stage/Stage.hpp"

#include "General/general.hpp"

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

		globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0x5754FC + 0xC00), mechanics::functions::changeGameRateFromBlueDashHit);

		globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0xAEF4F0 + 0xC00), Net::functions::calculateFrame);

		globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0xAF29E0 + 0xC00), Net::functions::randomNet);

		globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0xAEF2A0 + 0xC00), Net::functions::sub_140AEFEA0);

		globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0x6B39CC + 0xC00), Net::functions::checkFPSMatchmaking);

		globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0x74C648 + 0xC00), Battle::functions::matchCount);
		
		globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0x70C478 + 0xC00), Battle::functions::battleEnd);

		globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0x6E1310 + 0xC00), Battle::functions::loadDisconnectPopUp);
		
		globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0x74A8D4 + 0xC00), prop::functions::decreaseHealth);
		
		globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0x74A854 + 0xC00), prop::functions::decreaseChakra);
		
		globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0x74A954 + 0xC00), prop::functions::decreaseSupportGaugeS);

		globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0x74AE3C + 0xC00), prop::functions::decreaseSupportGaugeLS);

		globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0x76BE98 + 0xC00), prop::functions::decreaseGuardHealth);

		globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0x74AC10 + 0xC00), prop::functions::decreaseSubs);
		
		globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0x74AD24 + 0xC00), prop::functions::decreaseTools);

		globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0x74AAF8 + 0xC00), prop::functions::increaseStormGauge);

		globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0xA01230 + 0xC00), General::functions::getMemString);

		globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0xA43730 + 0xC00), General::functions::noMusicTrack);

		globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0x854F3C + 0xC00), General::functions::loadCpkInitial);

		globals::hookManager->hookAllEntries();

		ogWndProc = reinterpret_cast<WNDPROC>(GetWindowLongPtrA(sdk::game::gameWindow, GWLP_WNDPROC));

		SetWindowLongPtrA(sdk::game::gameWindow, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&functions::hkWndProc));
	}

	void uninitialize() noexcept {
		SetWindowLongPtrA(sdk::game::gameWindow, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(ogWndProc));

		globals::hookManager->unhookAllEntries();
		globals::hookManager->uninitialize();
	}
}
