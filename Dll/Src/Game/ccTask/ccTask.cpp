#include "pch.hpp"

#include "ccTask.hpp"

#include "Util/Console/Console.hpp"

__int64 __fastcall ccTask::Execute(DWORD* a1, int a2) {
	return globals::hookManager->callOriginal<decltype(&ccTask::Execute)>(ccTask::Execute, a1, a2);
	/*
	int pass = 0;
	//if ((*(__int64*)a1 + 0x18i64) == globals::moduleBase + 0xAB8330 + 0xC00)
		//util::console::debugPrint("asdf\n");
	for (int x = 0; x < memaddr.size(); x++) {
		if (__int64(a1) == memaddr[x])
			pass = 1;
	}
	if (pass == 0) {
		//util::console::debugPrint((std::to_string(memaddr.size()) + " " + std::to_string(__int64(a1)) + "\n").c_str());
		memaddr.push_back(__int64(a1));
		memaddrbool.push_back(true);
	}
	pass = 0;
	//for (int x = 0; x < memaddr.size(); x++) {
		//if (__int64(a1) == memaddr[x] && memaddrbool[x] == false)
			//pass = 1;
	//}
	//if (pass == 1)
		//util::console::debugPrint((std::to_string(memaddr.size()) + " " + std::to_string(__int64(a1)) + "\n").c_str());
	if (pass == 0)
		return globals::hookManager->callOriginal<decltype(&ccTask::Execute)>(ccTask::Execute, a1, a2);*/
}