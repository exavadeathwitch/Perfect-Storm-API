#include "pch.hpp"

#include "commandlist.hpp"

#include "Util/Memory/Modify.hpp"

#include "Util/Memory/String.hpp"

int __fastcall commandlist::functions::sub_140654FD8(__int64 a1, int* a2, const char* a3, int a4) {
	if (commandlist::combos == 1)
		if (a4 == 0)
			return globals::hookManager->callOriginal<decltype(&commandlist::functions::sub_140654FD8)>(commandlist::functions::sub_140654FD8, a1, a2, a3, a4);
		else
			return 0;
	return globals::hookManager->callOriginal<decltype(&commandlist::functions::sub_140654FD8)>(commandlist::functions::sub_140654FD8, a1, a2, a3, a4);
}
commandlist::character clchar;
__int64 __fastcall commandlist::functions::sub_140654848(__int64 a1) {
	typedef signed char(__fastcall* getCommandList) (__int64 a1);
	getCommandList getJutsuCommandList = (getCommandList)(globals::moduleBase + 0x654ED4 + 0xC00);
	typedef signed __int64(__fastcall* sub_7FF6BFE58250) ();
	sub_7FF6BFE58250 osub_7FF6BFE58250 = (sub_7FF6BFE58250)(globals::moduleBase + 0x657650 + 0xC00);
	typedef signed __int64(__fastcall* ccGame_GetPlayerLeader) (unsigned int a1);
	ccGame_GetPlayerLeader occGame_GetPlayerLeader = (ccGame_GetPlayerLeader)(globals::moduleBase + 0x85A948 + 0xC00);
	commandlist::customCLRun = 0;
	typedef signed __int64(__fastcall* ccGetCharCode) (int a1);
	ccGetCharCode occGetCharCode = (ccGetCharCode)(globals::moduleBase + 0x5289FC + 0xC00);
	unsigned int v2 = osub_7FF6BFE58250();
	__int64 PlayerLeader = occGame_GetPlayerLeader(v2);
	int* v4 = (int*)PlayerLeader;
	int characode = *(DWORD*)(PlayerLeader + 0xC8C);     // character code
	int costume = *(DWORD*)(PlayerLeader + 0xC94);     // costume number
	int ogawa = *(DWORD*)(PlayerLeader + 0xCBC);
	__int64 addr = occGetCharCode(characode);
	std::string characodestr = util::memory::String::strFromAddr(addr);
	clchar = commandlist::character(characodestr);
	*(DWORD*)(PlayerLeader + 0xCBC) = ogawa;
	if (clchar.isvalid()) {
		*(DWORD*)(PlayerLeader + 0xC94) = 0;
		if (*(DWORD*)(PlayerLeader + 0xCBC) == 1)
			clchar.awake = 1;
		else
			clchar.awake = 0;
		const std::array<unsigned char, 5> combocommandlist = util::memory::Modify::read_bytes<5>(globals::moduleBase + 0x654155 + 0xC00);
		const std::array<unsigned char, 5> jutsucommandlist = util::memory::Modify::read_bytes<5>(globals::moduleBase + 0x654182 + 0xC00);
		const std::array<unsigned char, 5> combocommandlist2 = util::memory::Modify::read_bytes<5>(globals::moduleBase + 0x654194 + 0xC00);
		util::memory::Modify::write_bytes<5>(globals::moduleBase + 0x654155 + 0xC00, { 0x90, 0x90, 0x90, 0x90, 0x90 });
		util::memory::Modify::write_bytes<5>(globals::moduleBase + 0x654182 + 0xC00, { 0x90, 0x90, 0x90, 0x90, 0x90 });
		util::memory::Modify::write_bytes<5>(globals::moduleBase + 0x654194 + 0xC00, { 0x90, 0x90, 0x90, 0x90, 0x90 });
		commandlist::customCLRun = 1;
		commandlist::combos = 1;
		commandlist::type = 0;
		clchar.readcombofile();
		clchar.readacombofile();
		clchar.readnamefile();
		clchar.readawakenamefile();
		
		if (clchar.awake == 0) {
			for (int x = 0; x < clchar.clsize; x++) {
				getJutsuCommandList(a1);
				clchar.index++;
			}
		}
		else {
			for (int x = 0; x < clchar.clasize; x++) {
				getJutsuCommandList(a1);
				clchar.aindex++;
			}
		}

		commandlist::combos = 0;
		getJutsuCommandList(a1);
		//commandlist::functions::sub_140654FD8(a1, v4, &commandlist::kgy[0], 0);
		auto retval = globals::hookManager->callOriginal<decltype(&commandlist::functions::sub_140654848)>(commandlist::functions::sub_140654848, a1);
		util::memory::Modify::write_bytes<5>(globals::moduleBase + 0x654155 + 0xC00, { combocommandlist[0], combocommandlist[1], combocommandlist[2], combocommandlist[3], combocommandlist[4] });
		util::memory::Modify::write_bytes<5>(globals::moduleBase + 0x654182 + 0xC00, { jutsucommandlist[0], jutsucommandlist[1], jutsucommandlist[2], jutsucommandlist[3], jutsucommandlist[4] });
		util::memory::Modify::write_bytes<5>(globals::moduleBase + 0x654194 + 0xC00, { combocommandlist2[0], combocommandlist2[1], combocommandlist2[2], combocommandlist2[3], combocommandlist2[4] });

		*(DWORD*)(PlayerLeader + 0xC8C) = characode;
		*(DWORD*)(PlayerLeader + 0xC94) = costume;
		return retval;
	}
	else
		return globals::hookManager->callOriginal<decltype(&commandlist::functions::sub_140654848)>(commandlist::functions::sub_140654848, a1);
}

__int64 __fastcall commandlist::functions::ccGetCharCode(__int64 a1, int a2) {
	__int64 retval = globals::hookManager->callOriginal<decltype(&commandlist::functions::ccGetCharCode)>(commandlist::functions::ccGetCharCode, a1, a2);
	if (commandlist::customCLRun == 1) {
		return (__int64)&commandlist::kgy;
	}
	return retval;
}

__int64* __fastcall commandlist::functions::strcpy(void* Dst, char* Src, size_t Size) {
	std::string src = Src;
	if (commandlist::customCLRun == 1 && src == "Kaguya Otsutsuki") {
		commandlist::customCLRun = 0;
		return globals::hookManager->getOriginal<decltype(&commandlist::functions::strcpy)>(commandlist::functions::strcpy)(Dst, &clchar.name[0], clchar.name.size());
	}
	if (commandlist::customCLRun == 1 && src == "Kaguya Otsutsuki (Awakening)") {
		commandlist::customCLRun = 0;
		return globals::hookManager->getOriginal<decltype(&commandlist::functions::strcpy)>(commandlist::functions::strcpy)(Dst, &clchar.awaname[0], clchar.awaname.size());
	}
	return globals::hookManager->getOriginal<decltype(&commandlist::functions::strcpy)>(commandlist::functions::strcpy)(Dst, Src, Size);
}

__int64 __fastcall commandlist::functions::ccUiGetMessage(__int64 MessageToDecode) {
	if (commandlist::combos == 1) {
		if (clchar.awake == 0) {
			if (commandlist::type == 0) {
				commandlist::type = 1;
				if (clchar.clnames[clchar.index].size() >= 16)
					return *(__int64*)(&clchar.clnames[clchar.index]);
				return (__int64)&clchar.clnames[clchar.index];

			}
			else {
				commandlist::type = 0;
				if (clchar.cldesc[clchar.index].size() >= 16)
					return *(__int64*)(&clchar.cldesc[clchar.index]);
				return (__int64)&clchar.cldesc[clchar.index];
			}
		}
		else {
			if (commandlist::type == 0) {
				commandlist::type = 1;
				if (clchar.clanames[clchar.aindex].size() >= 16)
					return *(__int64*)(&clchar.clanames[clchar.aindex]);
				return (__int64)&clchar.clanames[clchar.aindex];

			}
			else {
				commandlist::type = 0;
				if (clchar.cladesc[clchar.aindex].size() >= 16)
					return *(__int64*)(&clchar.cladesc[clchar.aindex]);
				return (__int64)&clchar.cladesc[clchar.aindex];
			}
		}
	}
	__int64 retval = globals::hookManager->getOriginal<decltype(&commandlist::functions::ccUiGetMessage)>(commandlist::functions::ccUiGetMessage)(MessageToDecode);
	return retval;
}

__int64 __fastcall commandlist::functions::ccReplaceStringTag(__int64* Src, char* a2, char* a3) {
	std::string src = a3;
	if (commandlist::customCLRun == 1 && src == "Kaguya Otsutsuki") {
		commandlist::customCLRun = 0;
		a2 = 0x0;
		a3 = &clchar.awaname[0];
	}
	return globals::hookManager->getOriginal<decltype(&commandlist::functions::ccReplaceStringTag)>(commandlist::functions::ccReplaceStringTag)(Src, a2, a3);
}