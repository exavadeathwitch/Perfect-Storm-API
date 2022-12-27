#include "pch.hpp"

#include "Hooks.hpp"

#include "Util/Memory/Memory.hpp"

#include "Util/Process/Module.hpp"

#include "Game/cc/ccGameObject/ccGameObject.hpp"

#include "Game/ccTaskManager/ccTaskManager.hpp"

#include "Game/ccTask/ccTask.hpp"

#include "Game/Framework/Framework.hpp"

#include "Game/misc/misc.hpp"

#include "Game/nuccSys/nuccSys.hpp"

#include "Util/Memory/Signature.hpp"

#include "Game/cc/ccPlayerSupport/ccPlayerSupport.hpp"
uint8_t a[] = { 0x0 };
using namespace util::memory::string_literals;
namespace hooks {
	void initialize() noexcept {
		//util::process::Module mod = util::process::Module("NSUNS4.exe");
		//constexpr auto example = { 0x0 };
		//const uint8_t example = { 0x0 };
		//util::memory::findSignature(mod, example, (uintptr_t)0x0, (uintptr_t)0x10);
		globals::hookManager->initialize();

		globals::hookManager->addEntry(sdk::game::swapChainVtbl[8], functions::hkPresent);

		globals::hookManager->addEntry(sdk::game::swapChainVtbl[13], functions::hkResizeBuffers);

		//globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0xAB7D30 + 0xC00), Framework::MainLoop);
		
		globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0xABD720 + 0xC00), ccTaskManager::Execute);

		globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0x3932A0 + 0xC00), ccGameObject::Update);

		globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0xAB8330 + 0xC00), ccTask::Execute);

		globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0x9E12E0 + 0xC00), misc::nummNXRequestDrawOpaqueCallback);

		//globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0x88D5F0 + 0xC00), misc::sub_7FF6C008E1F0);

		globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0x9DF050 + 0xC00), misc::sub_7FF6C01DFC50);

		globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0xA67610 + 0xC00), misc::updatescreen);

		//globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0x7E5624 + 0xC00), ccPlayerSupport::RequestSupportAction);

		//globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0x218538 + 0xC00), misc::getSupportAction);

		globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0xA0B980 + 0xC00), nuccSys::Update);

		//globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0x88BF70 + 0xC00), misc::sub_7FF6C008CB70);

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