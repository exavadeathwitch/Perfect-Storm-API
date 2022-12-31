#include "pch.hpp"

#include "Hooks.hpp"

#include "Util/Memory/Memory.hpp"

#include "Util/Process/Module.hpp"

#include "Util/Console/Console.hpp"

#include "Game/cc/ccGameObject/ccGameObject.hpp"

#include "Game/ccTaskManager/ccTaskManager.hpp"

#include "Game/ccTask/ccTask.hpp"

#include "Game/Framework/Framework.hpp"

#include "Game/misc/misc.hpp"

#include "Game/nucc/nuccSys/nuccSys.hpp"

#include "Util/Memory/Signature.hpp"

#include "Game/cc/ccPlayerSupport/ccPlayerSupport.hpp"

#include "Game/nucc/nuccLayer.hpp"

#include "Game/nucc/nuccFileLoadList.hpp"

#include "Game/ccScene/ccSceneManager.hpp"
__int64 GetAddressFromSignature(std::vector<int> signature, __int64 startaddress = 0, __int64 endaddress = 0) {
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    if (startaddress == 0) {
        startaddress = (__int64)(si.lpMinimumApplicationAddress);
    }
    if (endaddress == 0) {
        endaddress = (__int64)(si.lpMaximumApplicationAddress);
    }

    MEMORY_BASIC_INFORMATION mbi{ 0 };
    __int64 protectflags = (PAGE_GUARD | PAGE_NOCACHE | PAGE_NOACCESS);

    for (__int64 i = startaddress; i < endaddress - signature.size(); i++) {
        util::console::debugPrint(("scanning: " + std::to_string(i) +"\n"));
        if (VirtualQuery((LPCVOID)i, &mbi, sizeof(mbi))) {
            if (mbi.Protect & protectflags || !(mbi.State & MEM_COMMIT)) {
                util::console::debugPrint(("Bad Region! Region Base Address: " + std::to_string((__int64)mbi.BaseAddress) + " | Region end address: " + std::to_string((int)((__int64)mbi.BaseAddress + mbi.RegionSize)) + "\n"));
                i += mbi.RegionSize;
                continue; // if bad adress then dont read from it
            }
            util::console::debugPrint("Good Region! Region Base Address: " + std::to_string((__int64)mbi.BaseAddress) + " | Region end address: " + std::to_string((int)((__int64)mbi.BaseAddress + mbi.RegionSize)) + "\n");
            for (__int64 k = (__int64)mbi.BaseAddress; k < (__int64)mbi.BaseAddress + mbi.RegionSize - signature.size(); k++) {
                for (__int64 j = 0; j < signature.size(); j++) {
                    if (signature.at(j) != -1 && signature.at(j) != *(byte*)(k + j))
                        break;
                    if (j + 1 == signature.size()) {
                        std::cout << std::hex << k - globals::moduleBase - 0xC00 << std::endl;
                        return k;
                    }
                }
            }
            i = (__int64)mbi.BaseAddress + mbi.RegionSize;
        }
    }
    return NULL;
}

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

        globals::hookManager->hookEntry(functions::hkPresent);

        globals::hookManager->hookEntry(functions::hkResizeBuffers);

        globals::hookManager->addEntry(GetAddressFromSignature({ 0x48, 0x89, 0x5c, 0x24, -1, 0x48, 0x89, 0x6c, 0x24, -1, 0x56, 0x48, 0x83, 0xec, -1, 0x48, 0x8b, 0x01, 0x48, 0x8b, 0xf1 }, globals::moduleBase + 0xA90000, globals::moduleBase + 0xAE0000), ccSceneManager::Execute);

        globals::hookManager->hookEntry(ccSceneManager::Execute);

        globals::hookManager->addEntry(GetAddressFromSignature({ 0x48, 0x89, 0x74, 0x24, -1, 0x57, 0x48, 0x83, 0xec, -1, 0x48, 0x8b, 0x41, -1, 0x4c, 0x8d, 0x41, -1, 0x8b, 0xfa, 0x48, 0x8b, 0xf1, 0xba, -1, -1, -1, -1, 0x48, 0x85, 0xc0, 0x74, -1, 0x3b, 0xb8, -1, -1, -1, -1, 0x0f, 0x84, -1, -1, -1, -1, 0x49, 0x8b, 0x40, -1, 0x49, 0x83, 0xc0, -1, 0xff, 0xc2, 0x48, 0x85, 0xc0, 0x75, -1, 0x48, 0x8b, 0x01, 0x48, 0x89, 0x5c, 0x24, -1, 0x48, 0x89, 0x6c, 0x24, -1, 0xff, 0x50, -1, 0x48, 0x8b, 0x06, 0x48, 0x8b, 0xce, 0xff, 0x50, -1, 0x48, 0x8b, 0x4e, -1, 0x33, 0xed, 0x48, 0x85, 0xc9, 0x74, -1, 0x48, 0x8b, 0x01, 0x8d, 0x55, -1, 0xff, 0x10, 0x48, 0x89, 0x6e, -1, 0x48, 0x8b, 0x06, 0x48, 0x8b, 0xce, 0xff, 0x50, -1, 0x44, 0x0f, 0xb6, 0x46, -1, 0x48, 0x8b, 0x56, -1, 0x4c, 0x8d, 0x0d, -1, -1, -1, -1, 0xb9, -1, -1, -1, -1, 0xc7, 0x44, 0x24, -1, -1, -1, -1, -1, 0xe8, -1, -1, -1, -1, 0x48, 0x8b, 0xd8, 0x48, 0x85, 0xc0, 0x74, -1, 0x48, 0x8b, 0xc8, 0xe8, -1, -1, -1, -1, 0x48, 0x8d, 0x05, -1, -1, -1, -1, 0x48, 0x89, 0x6b, -1, 0x48, 0x89, 0x03, 0x89, 0x6b, -1, 0x48, 0x89, 0x6b, -1, 0xc6, 0x43, -1, -1, 0xeb, -1, 0x83, 0xfa, -1, 0x0f, 0x84, -1, -1, -1, -1, 0x48, 0x8b, 0x41, -1, 0x48, 0x8b, 0x40, -1, 0x80, 0x78, -1, -1, 0x0f, 0x85, -1, -1, -1, -1, 0x0f, 0x1f, 0x00, 0x39, 0x78, -1, 0x7d, -1, 0x48, 0x8b, 0x40, -1, 0xeb, -1, 0x48, 0x8b, 0x00, 0x80, 0x78, -1, -1, 0x74, -1, 0x48, 0x8b, 0x74, 0x24, -1, 0x48, 0x83, 0xc4, -1, 0x5f, 0xc3, 0x48, 0x8b, 0xdd, 0x48, 0x89, 0x5e, -1, 0x48, 0x8b, 0x03, 0x48, 0x8b, 0xcb, 0xff, 0x50, -1, 0x41, 0xb8 }, globals::moduleBase + 0xA90000, globals::moduleBase + 0xAE0000), ccSceneManager::Push);

        globals::hookManager->hookEntry(ccSceneManager::Push);
        
        //globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0xABD720 + 0xC00), ccTaskManager::Execute);
		globals::hookManager->addEntry(GetAddressFromSignature({ 0x40, 0x55, 0x56, 0x48, 0x83, 0xec, -1, 0x81, 0xfa }, globals::moduleBase + 0xAB0000, globals::moduleBase + 0xAC0000), ccTaskManager::Execute);

		//globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0x3932A0 + 0xC00), ccGameObject::Update);

		globals::hookManager->addEntry(GetAddressFromSignature({ 0x83, 0x79, -1, -1, 0x74, -1, 0x85, 0x51 }, globals::moduleBase + 0xAB0000, globals::moduleBase + 0xAC0000), ccTask::Execute);
		
        globals::hookManager->addEntry(GetAddressFromSignature({0x40, 0x57, 0x48, 0x83, 0xec, -1, 0x48, 0x8b, 0xf9, 0xe8, -1, -1, -1, -1, 0x83, 0x7f }, globals::moduleBase + 0xA20000, globals::moduleBase + 0xAA0000), nuccLayer::ExecuteDrawCommand);
        
        globals::hookManager->addEntry(GetAddressFromSignature({ 0x48, 0x89, 0x5c, 0x24, -1, 0x55, 0x57, 0x41, 0x54, 0x41, 0x56, 0x41, 0x57, 0x48, 0x83, 0xec }, globals::moduleBase + 0x9F0000, globals::moduleBase + 0xA70000), nuccFileLoadList::Load);
        
        globals::hookManager->addEntry(GetAddressFromSignature({ 0x48, 0x89, 0x5c, 0x24, -1, 0x57, 0x48, 0x83, 0xec, -1, 0x48, 0x8b, 0xd9, 0xb9, -1, -1, -1, -1, 0xff, 0x15 }, globals::moduleBase + 0x170000, globals::moduleBase + 0x250000), misc::processkeyboardinput);
        
        globals::hookManager->addEntry(GetAddressFromSignature({ 0x40, 0x53, 0x48, 0x83, 0xec, -1, 0x48, 0x8b, 0xd9, 0x48, 0x8b, 0x0d, -1, -1, -1, -1, 0x33, 0xd2, 0x39, 0x91 }, globals::moduleBase + 0x990000, globals::moduleBase + 0xA30000), misc::nohud);
        
        globals::hookManager->addEntry(GetAddressFromSignature({ 0x48, 0x8b, 0xc4, 0x48, 0x89, 0x58, -1, 0x48, 0x89, 0x70, -1, 0x48, 0x89, 0x78, -1, 0x55, 0x48, 0x8d, 0x68, -1, 0x48, 0x81, 0xec, -1, -1, -1, -1, 0x48, 0x8b, 0xf1, 0x48, 0x8b, 0x89, -1, -1,
-1, -1, 0x0f, 0x29, 0x70, -1, 0x48, 0x85, 0xc9, 0x0f, 0x84, -1, -1, -1, -1, 0xe8, -1, -1, -1, -1, 0x85, 0xc0, 0x0f, 0x84, -1, -1, -1, -1, 0x48, 0x8d, 0x4c, 0x24 }, globals::moduleBase + 0x5B0000, globals::moduleBase + 0x640000), misc::rostercoord);


        globals::hookManager->addEntry(GetAddressFromSignature({ 0x48, 0x89, 0x5c, 0x24, -1, 0x57, 0x48, 0x83, 0xec, -1, 0x48, 0x8d, 0x59, -1, 0xbf, -1, -1, -1, -1, 0x48, 0x8b, 0x0b, 0x48, 0x85, 0xc9, 0x74, -1, 0xe8, -1, -1, -1, -1, 0x48, 0x83, 0xc3, -1,
0x48, 0xff, 0xcf, 0x75, -1, 0x48, 0x8b, 0x5c, 0x24, -1, 0x48, 0x83, 0xc4, -1 }, globals::moduleBase + 0x5C0000, globals::moduleBase + 0x620000), misc::initCharselModel);

        globals::hookManager->addEntry(GetAddressFromSignature({ 0x40, 0x53, 0x48, 0x83, 0xec, -1, 0x48, 0x8b, 0x01, 0x48, 0x8b, 0xd9, 0xff, 0x50, -1, 0x83, 0x7b, -1, -1, 0x74, -1, 0x48, 0x63, 0x43, -1, 0x85, 0xc0, 0x78, -1, 0x3b, 0x43, -1, 0x7d, -1, 0x48, 0x8b, 0x53 }, globals::moduleBase + 0x2F0000, globals::moduleBase + 0x360000), misc::modelCtrl);
		//globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0x9E12E0 + 0xC00), misc::nummNXRequestDrawOpaqueCallback);

		//globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0x88D5F0 + 0xC00), misc::sub_7FF6C008E1F0);

		//globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0x9DF050 + 0xC00), misc::sub_7FF6C01DFC50);

		//globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0xA67610 + 0xC00), misc::updatescreen);

		//globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0x7E5624 + 0xC00), ccPlayerSupport::RequestSupportAction);

		//globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0x218538 + 0xC00), misc::getSupportAction);

		//globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0xA0B980 + 0xC00), nuccSys::Update);

		//globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0x88BF70 + 0xC00), misc::sub_7FF6C008CB70);

        //__int64 mainloopaddr = GetAddressFromSignature({ 0x40, 0x53, 0x48, 0x83, 0xec, -1, 0x48, 0x8b, 0xd9, 0x0f, 0x1f, 0x80, -1, -1, -1, -1, 0x48, 0x8b, 0x0d }, globals::moduleBase + 0xAB0000, globals::moduleBase + 0xAC0000);

        //globals::hookManager->addEntry((std::uintptr_t)mainloopaddr, Framework::MainLoop);

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