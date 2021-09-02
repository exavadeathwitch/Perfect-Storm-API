#include "pch.hpp"

#include "Hooks.hpp"

#include "Core/Globals.hpp"


_int64 __fastcall nCanYouShuriken(__int64 a1)
{
	/*
	int retval = globals::hookManager->getOriginal<decltype(&nCanYouShuriken)>(nCanYouShuriken, a1);
		return retval;
*/
	__int64 v1; // rbx@1
	signed int v2; // ecx@6
	__int64 result; // rax@10


	signed typedef __int64(__fastcall* sub_14076C79C) (__int64 a1);
	sub_14076C79C osub_14076C79C = (sub_14076C79C)(globals::moduleBase + 0x76BB9C + 0xC00);

	typedef __int64(__fastcall* sub_14077DA68) (__int64 a1, int a2, __int64 a3);
	sub_14077DA68 osub_14077DA68 = (sub_14077DA68)(globals::moduleBase + 0x77CE68 + 0xC00);

	v1 = a1;
	result = 0;
	if (*(DWORD*)(a1 + 0x14B30))
	{
		if ((*(int(__fastcall**)(__int64, signed __int64))(*(__int64*)a1 + 0x1398i64))(a1, 6i64))
		{
			if (!(unsigned int)osub_14076C79C(8i64))
			{
				if (osub_14077DA68(v1, 151, 1i64))
				{
					if (*(DWORD*)(v1 + 0x141EC))
					{
						v2 = *(DWORD*)(v1 + 0xCC0);
						if (v2 > 0 && ((v2 <= 2 || v2 == 8 || v2 == 66 || v2 == 63))) //&& (*(int(__fastcall**)(__int64))(*(__int64*)v1 + 0xE60i64))(v1)))
							result = 1;
					}
				}
			}
		}
	}
	return result;
}

namespace hooks {
	void initialize() noexcept {
		globals::hookManager->initialize();

		globals::hookManager->addEntry(sdk::game::swapChainVtbl[8], functions::hkPresent);
		
		globals::hookManager->addEntry((std::uintptr_t)(globals::moduleBase + 0x7AD024 + 0xC00), nCanYouShuriken);

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
