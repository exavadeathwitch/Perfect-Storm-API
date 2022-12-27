#include "pch.hpp"

#include "misc.hpp"

#include "Util/Console/Console.hpp"

#include "Util/Memory/Modify.hpp"

#include "Core/DebugMenu/GameSpeed/GameSpeed.hpp"
uint8_t call[] = { 0xE8, 0x37, 0xDD, 0xFF, 0xFF };
bool retgarbage = false;
int run = 0;
int run2 = 0;
std::vector<__int64> v8vec;
__int64 __fastcall misc::nummNXRequestDrawOpaqueCallback(__int64 a1, __int64 a2) {
	run2 = 1;
	if (a1 == (__int64)(globals::moduleBase + 0x9A9A94) && start) {
		additional = a2;
		//util::console::debugPrint("asdf\n");
		retgarbage = true;
		if (start) {
			//for (int x = 0; x < 5; x++)
				//util::memory::Modify::write_bytes<1>(globals::moduleBase + 0x9E1314 + 0xC00 + x, { 0x90 });
		}
		run = 1;
		//if (test5 == 1)
			//run = 0;
	}
	auto retval = globals::hookManager->callOriginal<decltype(&misc::nummNXRequestDrawOpaqueCallback)>(misc::nummNXRequestDrawOpaqueCallback, a1, a2);
	for (int x = 0; x < 5; x++)
		util::memory::Modify::write_bytes<1>(globals::moduleBase + 0x9E1314 + 0xC00 + x, {call[x]});
	run = 0;
	run2 = 0;
	return retval;
}
__int64* a11;
__int64 a22;
__int64 v8out = NULL;
int first = 0;
int arrval = 3;
int bytearr[] = { 0x1101670, 0x1101648, 0x11015D0, 0x1101698 };

__int64 __fastcall misc::sub_7FF6C01DFC50(__int64* a1, __int64 a2) {
	if (first == 0) {
		__int64* a11 = a1;
		__int64 a22 = a2;
		first = 1;
	}
	__int64* v2; // rdi
	__int64 v5; // rcx
	__int64 v6; // rdx
	__int64 v7; // rbx
	__int64 v8; // rbx
	__int64 v9; // rax
	__int64 v10; // rax
	__int64* v11; // rax

	int in = 0;
	
	v2 = (__int64*)*a1;
	if ((unsigned __int64)(*(__int64*)(*a1 + 16) + 72i64) > *(__int64*)(*a1 + 24))
	{
		v5 = *(__int64*)(v2[1] + 8i64);
		if (v5)
		{
			v2[1] = v5;
			v2[2] = 0i64;
		}
	}
	v6 = v2[2];
	v7 = *(__int64*)v2[1];
	v2[5] += 72i64;
	v2[2] = v6 + 72;
	v8 = v6 + v7;
	for (int x = 0; x < v8vec.size(); x++) {
		if (v8 == v8vec[x])
			in = 1;
	}
	if (in == 0 && run == 0)
		v8vec.push_back(v8);
		
	if (run == 0) {
		return globals::hookManager->callOriginal<decltype(&misc::sub_7FF6C01DFC50)>(misc::sub_7FF6C01DFC50, a1, a2);
	}

	v2 = (__int64*)*a1;
	/*
	if ((unsigned __int64)(*(__int64*)(*a1 + 16) + 72i64) > *(__int64*)(*a1 + 24))
	{
		v5 = *(__int64*)(v2[1] + 8i64);
		if (v5)
		{
			v2[1] = v5;
			v2[2] = 0i64;
		}
	}
	
	v6 = v2[2];
	v7 = *(__int64*)v2[1];
	v2[5] += 72i64;
	v2[2] = v6 + 72;
	v8 = v6 + v7;
	*/
	if ((unsigned __int64)(*(__int64*)(*a1 + 16) + 72i64) > *(__int64*)(*a1 + 24))
	{
		v5 = *(__int64*)(v2[1] + 8i64);
		if (v5)
		{
			v2[1] = v5;
			v2[2] = 0i64;
		}
	}
	v6 = v2[2];
	v7 = *(__int64*)v2[1];
	v2[5] += 72i64;
	v2[2] = v6 + 72;
	v8 = v6 + v7;
	if (v8)
	{
		v9 = *a1;
		*(__int64*)(v8 + 8) = a2;
		*(__int64*)(v8 + 16) = 0i64;
		*(__int64*)(v8 + 32) = v9;
		*(DWORD*)(v8 + 40) = 31;//31;
		*(__int64*)v8 = globals::moduleBase + bytearr[arrval];
		*(__int64*)v8 = globals::moduleBase + 0x1101698;
		//*(__int64*)v8 = globals::moduleBase + 0x1101670;
		//*(__int64*)v8 = globals::moduleBase + 0x1101648;
		*(__int64*)v8 = globals::moduleBase + 0x1101620;
		//*(__int64*)v8 = globals::moduleBase + 0x11015F8;
		//*(__int64*)v8 = globals::moduleBase + 0x11014D8;
		//*(__int64*)v8 = globals::moduleBase + 0x1101560;
		//*(__int64*)v8 = globals::moduleBase + 0x1101518;
		//*(__int64*)v8 = globals::moduleBase + 0x1101910;
		//*(__int64*)v8 = globals::moduleBase + 0x1101D08;
		//*(__int64*)v8 = globals::moduleBase + 0x1101CE0;
		//*(__int64*)v8 = globals::moduleBase + 0x12F8E38;
		//*(__int64*)v8 = globals::moduleBase + 0x12F8E60;
		*(__int64*)(v8 + 24) = v8;
		//arrval++;
		//if (arrval > 2)
			//arrval = 0;
	}
	std::cout << std::hex << v8 << std::endl;
	v10 = a1[10];
	
	if (v10 && a1[9] == a2)
	{
		*(__int64*)(*(__int64*)(v10 + 24) + 16i64) = v8;
		v8out = v8;
		*(__int64*)(v10 + 24) = v8;
	}
	return v8;
}


char __fastcall misc::sub_7FF6C008E1F0(__m128* a1, __int64* a2) {
	std::cout << "a1: " << std::hex << a1 << std::endl;
	std::cout << "a2: " << std::hex << a2 << std::endl;
	return globals::hookManager->callOriginal<decltype(&misc::sub_7FF6C008E1F0)>(misc::sub_7FF6C008E1F0, a1, a2);
}

__int64 __fastcall misc::sub_7FF6C008CB70(__int64 a1, int a2) {
	if (run && v8out != NULL && globals::hookManager->callOriginal<decltype(&misc::sub_7FF6C008CB70)>(misc::sub_7FF6C008CB70, a1, a2) == 0)
		return v8out;
	return globals::hookManager->callOriginal<decltype(&misc::sub_7FF6C008CB70)>(misc::sub_7FF6C008CB70, a1, a2);
}

void __fastcall misc::updatescreen(__int64 a1) {
	//if (test5 == 0)
		return globals::hookManager->callOriginal<decltype(&misc::updatescreen)>(misc::updatescreen, a1);
	util::console::debugPrint("asdf\n");
	return;
}