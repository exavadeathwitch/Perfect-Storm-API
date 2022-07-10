#include "pch.hpp"

#include "engine.hpp"

#include <iostream>

#include "GGPO/ggponet.h"

#include "Core/Online/online.hpp"

#include "Util/Memory/String.hpp"

#include "Util/Memory/Modify.hpp"

int __fastcall engine::Engine::gamelogic(DWORD* a1) {
	return globals::hookManager->callOriginal<decltype(&engine::Engine::gamelogic)>(engine::Engine::gamelogic, a1);
};

__int64 __fastcall engine::Engine::pauseState(__int64 a1) {
	if (engine::runEngine)
		return globals::hookManager->callOriginal<decltype(&engine::Engine::pauseState)>(engine::Engine::pauseState, a1);
	return 0;
};

int __fastcall engine::Engine::battleStart(__int64 a1, int a2) {
	engine::inBattle = 1;
	return globals::hookManager->callOriginal<decltype(&engine::Engine::battleStart)>(engine::Engine::battleStart, a1, a2);
}

int __fastcall engine::Engine::outBattle(__int64 a1) {
	engine::inBattle = 0;
	engine::charsel = 1;
	return globals::hookManager->callOriginal<decltype(&engine::Engine::outBattle)>(engine::Engine::outBattle, a1);
}

int __fastcall engine::Engine::menuControl(__int64 a1) {
	int premenuselect = *(DWORD*)(a1 + 208);
	const auto retval = globals::hookManager->getOriginal<decltype(&engine::Engine::menuControl)>(engine::Engine::menuControl)(a1);
	int postmenuselect = *(DWORD*)(a1 + 208);
	if (S1API::enableOnline == 1 && postmenuselect == 2){
		*(DWORD*)(a1 + 208) = 0;
		S1API::enableOnline = 0;
		std::cout << "Online Disabled" << std::endl;
	}
	if (S1API::enableOnline == 1 && postmenuselect == 0) {
		*(DWORD*)(a1 + 208) = 2;
		S1API::enableOnline = 0;
		std::cout << "Online Disabled" << std::endl;
	}
	if (premenuselect == 2 && postmenuselect == 0) {
		*(DWORD*)(a1 + 208) = 1;
		S1API::enableOnline = 1;
		std::cout << "Online Enabled" << std::endl;
	}
	if (premenuselect == 0 && postmenuselect == 2) {
		*(DWORD*)(a1 + 208) = 1;
		S1API::enableOnline = 1;
		std::cout << "Online Enabled" << std::endl;
	}
	return retval;
}

__int64 __fastcall engine::Engine::loadText(__int64 a1) {
	const auto retval = globals::hookManager->getOriginal<decltype(&engine::Engine::loadText)>(engine::Engine::loadText)(a1);
	std::string test = "test";
	if (util::memory::String::strFromAddr(a1) == "Challenge friends or the COM in battle." && S1API::enableOnline == 1)
		util::memory::Modify::write_bytes<67>(a1, { 0x4F, 0x6E, 0x6C, 0x69, 0x6E, 0x65, 0x20, 0x4D, 0x6F, 0x64, 0x65, 0x3A, 0x20, 0x43, 0x68, 0x61, 0x6C, 0x6C, 0x65, 0x6E, 0x67, 0x65, 0x20, 0x6F, 0x70, 0x70, 0x6F, 0x6E, 0x65, 0x6E, 0x74, 0x73, 0x20, 0x74, 0x6F, 0x20, 0x62, 0x61, 0x74, 0x74, 0x6C, 0x65, 0x20, 0x66, 0x72, 0x6F, 0x6D, 0x20, 0x61, 0x6C, 0x6C, 0x20, 0x6F, 0x76, 0x65, 0x72, 0x20, 0x74, 0x68, 0x65, 0x20, 0x77, 0x6F, 0x72, 0x6C, 0x64, 0x2E });
	if (util::memory::String::strFromAddr(a1) == "Online Mode: Challenge opponents to battle from all over the world." && S1API::enableOnline == 0)
		util::memory::Modify::write_bytes<67>(a1, { 0x43, 0x68, 0x61, 0x6C, 0x6C, 0x65, 0x6E, 0x67, 0x65, 0x20, 0x66, 0x72, 0x69, 0x65, 0x6E, 0x64, 0x73, 0x20, 0x6F, 0x72, 0x20, 0x74, 0x68, 0x65, 0x20, 0x43, 0x4F, 0x4D, 0x20, 0x69, 0x6E, 0x20, 0x62, 0x61, 0x74, 0x74, 0x6C, 0x65, 0x2E, 0x00, 0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6D, 0x69, 0x73, 0x73, 0x69, 0x6F, 0x6E, 0x5F, 0x6D, 0x61, 0x69, 0x6E, 0x61, 0x63, 0x74, 0x5F, 0x30, 0x31, 0x31 });
	return retval;
}

DWORD* __fastcall engine::Engine::initStuff(__int64* a1, __int64 a2, __int64 a3) {
	if (util::memory::String::strFromAddr(a3) == "Join_STEAM") {
		std::cout << "Character Select Started" << std::endl;
		engine::charsel = 1;
	}
	return globals::hookManager->callOriginal<decltype(&engine::Engine::initStuff)>(engine::Engine::initStuff, a1, a2, a3);
}

__int64* __fastcall engine::Engine::enableWindow(__int64* a1, __int64 a2)
{
	if (engine::charsel == 1 && S1API::enableOnline == 1) {
		if ((*((__int64*)a1 + 0x7A)) != 0)
			*((__int64*)a1 + 0x7A) = 0;
	}
	const auto retval = globals::hookManager->callOriginal<decltype(&engine::Engine::enableWindow)>(engine::Engine::enableWindow, a1, a2);
	return retval;
}
__int64 __fastcall engine::Engine::ccGameManager_Play(__int64 a1) {
	__int64 v33;

	typedef __int64(__fastcall* operator_new_caller) (size_t a1, __int64 a2, int a3);
	operator_new_caller ooperator_new_caller = (operator_new_caller)(globals::moduleBase + 0x47E110 + 0xC00);

	typedef __int64(__fastcall* ccGameModeSel) (__int64 a1);
	ccGameModeSel occGameModeSel = (ccGameModeSel)(globals::moduleBase + 0x27F464 + 0xC00);

	typedef __int64(__fastcall* Main) (__int64 a1);
	Main main = (Main)(globals::moduleBase + 0x27FB48 + 0xC00);

	typedef __int64(__fastcall* _ccGameModeSel) (__int64 a1);
	_ccGameModeSel _occGameModeSel = (_ccGameModeSel)(globals::moduleBase + 0x27F518 + 0xC00);

	typedef int(__fastcall* d) (__int64 a1);
	d oRequestEndGameMode = (d)(globals::moduleBase + 0x250CBC + 0xC00);

	typedef __int64(__fastcall* exit) (__int64 a1);
	exit Exit = (exit)(globals::moduleBase + 0x27F660 + 0xC00);

	typedef __int64(__fastcall* ex) (__int64 a1, int a2);
	ex lex = (ex)(globals::moduleBase + 0x24F38C + 0xC00);

	typedef void(__fastcall* sub_1401EB498) (__int64 *a1);
	sub_1401EB498 osub_1401EB498 = (sub_1401EB498)(globals::moduleBase + 0x1EA898 + 0xC00);

	typedef void(__fastcall* sub_14041206C) (__int64 a1, __int64 a2, __int64 a3);
	sub_14041206C osub_14041206C = (sub_14041206C)(globals::moduleBase + 0x41146C + 0xC00);

	typedef __int64(__fastcall* sub_14024B744) (__int64 a1, unsigned int a2);
	sub_14024B744 osub_14024B744 = (sub_14024B744)(globals::moduleBase + 0x24AB44 + 0xC00);

	typedef __int64(__fastcall* sub_14019DA3C) (__int64 a1, int a2);
	sub_14019DA3C osub_14019DA3C = (sub_14019DA3C)(globals::moduleBase + 0x19CE3C + 0xC00);
	

	//std::cout << "crap " << std::hex << a1 << std::endl;
	if (engine::triggerMenu) {

		//*(__int64*)(a1 + 3464) = 0;
		//*(DWORD*)(a1 + 0x38) = 5;
		}//osub_1401EB498((__int64*)a1 + 92);
		//oRequestEndGameMode(*(int*)(a1 + 0xD88));
		//oRequestEndGameMode(*(__int64*)(a1 + 3464));
		//std::cout << std::hex << a1 + 0x38 << std::endl;
		//lex(a1, 1);
		//*(DWORD*)(a1 + 0x38) = 5;
		//*(__int64*)(a1 + 0xD80) = occGameModeSel(ooperator_new_caller(0xF0ui64, (__int64)"source\\game.cpp", 0x4CD));
	

	return globals::hookManager->callOriginal<decltype(&engine::Engine::ccGameManager_Play)>(engine::Engine::ccGameManager_Play, a1);
	return 0;
}
typedef void(__fastcall* sub_14041206C) (__int64 a1, __int64 a2, __int64 a3);
sub_14041206C osub_14041206C = (sub_14041206C)(globals::moduleBase + 0x41146C + 0xC00);

typedef __int64(__fastcall* sub_14024B744) (__int64 a1, unsigned int a2);
sub_14024B744 osub_14024B744 = (sub_14024B744)(globals::moduleBase + 0x24AB44 + 0xC00);

typedef __int64(__fastcall* sub_14019DA3C) (__int64 a1, int a2);
sub_14019DA3C osub_14019DA3C = (sub_14019DA3C)(globals::moduleBase + 0x19CE3C + 0xC00);

signed __int64 __fastcall engine::Engine::MainProcess(__int64 a1) {
	const auto retval = globals::hookManager->callOriginal<decltype(&engine::Engine::MainProcess)>(engine::Engine::MainProcess, a1);
	/*//*(unsigned int*)(a1 + 0x38) = 0;
	if (engine::triggerMenu) {
		*(unsigned int*)(a1 + 0x38) = 1;
		engine::Engine::LoadExpectedScene(*(__int64*)(globals::moduleBase + 0x86DD48), 1);
		osub_14041206C(*(__int64*)(globals::moduleBase + 0x877E40), 2i64, 30i64);
		osub_14024B744(*(__int64*)(globals::moduleBase + 0x86DCB0), 3000);
		osub_14019DA3C(a1 + 48, 1);

	
	*v3 = 0;
	engine::Engine::LoadExpectedScene(a1, 1);
	osub_14041206C(globals::moduleBase + 0x877E40, 2i64, 30i64);
	osub_14024B744(globals::moduleBase + 0x86DCB0, 3000);
	osub_14019DA3C(a1 + 48, 1);
	engine::triggerMenu = 0;
	}*/
	return retval;
}
__int64 __fastcall engine::Engine::LoadExpectedScene(__int64 a1, int a2) {
	//std::cout << std::hex << a2 << std::dec << std::endl;
	return globals::hookManager->callOriginal<decltype(&engine::Engine::LoadExpectedScene)>(engine::Engine::LoadExpectedScene, a1, a2);
}
int __fastcall engine::Engine::resultsignal(__int64 a1) {
	if (S1API::enableOnline == 0) {
		*(DWORD*)(a1 + 0x404) = 0;
		*(DWORD*)(a1 + 0x8) = 0;
		return globals::hookManager->callOriginal<decltype(&engine::Engine::resultsignal)>(engine::Engine::resultsignal, a1);
	}
	engine::Engine::LoadExpectedScene(*(__int64*)(globals::moduleBase + 0x86DD48), 1);
	*(DWORD*)(a1) = 25;
	*(DWORD*)(a1 + 0x404) = 3;
	return 1;
	//std::cout << std::hex << a2 << std::dec << std::endl;
}
int __fastcall engine::Engine::withoutwin(__int64 a1) {
	if (S1API::enableOnline == 0) {
		*(DWORD*)(a1 + 0x404) = 0;
		*(DWORD*)(a1 + 0x8) = 0;
		return globals::hookManager->callOriginal<decltype(&engine::Engine::withoutwin)>(engine::Engine::withoutwin, a1);
	}
	engine::Engine::LoadExpectedScene(*(__int64*)(globals::moduleBase + 0x86DD48), 1);
	*(DWORD*)(a1) = 25;
	*(DWORD*)(a1 + 0x404) = 3;
	return 1;
	//std::cout << std::hex << a2 << std::dec << std::endl;
}
__int64 __fastcall engine::Engine::gameduelmain(__int64 a1) {
	std::cout << *(DWORD*)a1 << std::endl;
	if (engine::triggerMenu == 1) {
		*(unsigned int*)(a1 + 0x38) = 5;
		engine::Engine::LoadExpectedScene(*(__int64*)(globals::moduleBase + 0x86DD48), 1);
		*(DWORD*)(a1) = 25;
		*(DWORD*)(a1 + 0x404) = 0;
		*(DWORD*)(a1 + 0x8) = 2;/*
		osub_14041206C(*(__int64*)(globals::moduleBase + 0x877E40), 2i64, 30i64);
		osub_14024B744(*(__int64*)(globals::moduleBase + 0x86DCB0), 3000);
		osub_14019DA3C(a1 + 48, 1);*/
		engine::triggerMenu = 0;
	}
	return globals::hookManager->callOriginal<decltype(&engine::Engine::gameduelmain)>(engine::Engine::gameduelmain, a1);
}