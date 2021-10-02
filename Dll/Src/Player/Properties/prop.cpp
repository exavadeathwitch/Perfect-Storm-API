#include "pch.hpp"

#include "prop.hpp"

#include "Net/Online Training/oTraining.hpp"

#include <iostream>
signed __int64 __fastcall prop::functions::decreaseHealth(__int64 a1, __int64 a2, float Damage)
{
	//return globals::hookManager->callOriginal<decltype(&prop::functions::decreaseHealth)>(prop::functions::decreaseHealth, a1, a2, Damage);
	//return retval;
	signed __int64 PlayerAddr; // rax@1
	float Health; // xmm0_4@2

	typedef signed __int64(__fastcall* FindPlayerAddr) (__int64 a1, unsigned int a2);
	FindPlayerAddr oFindPlayerAddr = (FindPlayerAddr)(globals::moduleBase + 0x74A71C + 0xC00);
	PlayerAddr = oFindPlayerAddr(a1, a2);
	if (PlayerAddr)
	{
		Health = *(float*)(PlayerAddr + 0x10);
		if (Health != 0.0)
			switch (OTraining::selectedLItem)
			{
			case 0:
				*(float*)(PlayerAddr + 0x10) = Health - Damage;
				break;
			case 1:
				*(float*)(PlayerAddr + 0x10) = 100.0f;
				break;
			case 2:
				*(float*)(PlayerAddr + 0x10) = 30.0f;
				break;
			}
	}
	return PlayerAddr;
	//if (Debug)	cout << endl << "PlayerAddr: " << PlayerAddr << endl << "Old Health: " << Health << endl << "Damage Taken: " << Damage << endl << "New Health: " << Health - Damage << endl; //Damage Values

}

signed __int64 __fastcall prop::functions::decreaseChakra(__int64 a1, __int64 a2, float ChakraCost)
{
	signed __int64 PlayerStateAddr; // rax@1
	float CurrentChakra; // xmm0_4@2
	std::uintptr_t addrGameBase = (std::uintptr_t)GetModuleHandle(NULL);
	typedef signed __int64(__fastcall* FindPlayerAddr) (__int64 a1, unsigned int a2);
	FindPlayerAddr oFindPlayerAddr = (FindPlayerAddr)(addrGameBase + 0x74A71C + 0xC00);

	PlayerStateAddr = oFindPlayerAddr(a1, a2);
	if (PlayerStateAddr)
	{
		CurrentChakra = *(float*)(PlayerStateAddr + 0x18);
		if (CurrentChakra != 0.0)
			if (OTraining::tcheckBox[0] == true)
			{
				*(float*)(PlayerStateAddr + 0x18) = 100.0f;
			}
			else
			{
				*(float*)(PlayerStateAddr + 0x18) = CurrentChakra - ChakraCost;
			}
	}
	//if (Debug)	cout << endl << "PlayerAddr: " << PlayerStateAddr << endl << "Current Chakra: " << CurrentChakra << endl << "Chakra Cost: " << ChakraCost << endl << "Net Chakra: " << CurrentChakra - ChakraCost << endl; //Chakra Values
	return PlayerStateAddr;
}

signed __int64 __fastcall prop::functions::decreaseSupportGaugeS(__int64 a1, __int64 a2, float SupportCost)
{
	signed __int64 PlayerStateAddr; // rax@1
	float CurrentSupportGauge; // xmm0_4@2 Decreases support gauge as a result of a support being called for a support jutsu. Not for switching.
	typedef signed __int64(__fastcall* sub_140746CE8) (__int64 a1, int a2);
	sub_140746CE8 osub_140746CE8 = (sub_140746CE8)(globals::moduleBase + 0x74A76C + 0xC00);
	PlayerStateAddr = osub_140746CE8(a1, a2);
	if (PlayerStateAddr)
	{
		CurrentSupportGauge = *(float*)(PlayerStateAddr + 0x2C);
		if (CurrentSupportGauge != 0.0)
			if (OTraining::tcheckBox[1] == true)
			{
				*(float*)(PlayerStateAddr + 0x2C) = 100.0f;
			}
			else
			{
				*(float*)(PlayerStateAddr + 0x2C) = CurrentSupportGauge - SupportCost;
			}
	}
	return PlayerStateAddr;
}

signed __int64 __fastcall prop::functions::decreaseSupportGaugeLS(__int64 a1, int a2, int Uselessvar, int NewSupportGaugeLevel)
{
	if (OTraining::tcheckBox[1] == true)
	{
		signed __int64 PlayerStateAddr; // rax@1 Decreases support gauge as a result of switching. Not for support jutsu.
		typedef signed __int64(__fastcall* sub_140746CE8) (__int64 a1, int a2);
		sub_140746CE8 osub_140746CE8 = (sub_140746CE8)(globals::moduleBase + 0x74A76C + 0xC00);
		PlayerStateAddr = osub_140746CE8(a1, a2);
		if (PlayerStateAddr)
		{
			*(float*)(PlayerStateAddr + 0x2C) = 100.0f;
		}
		return PlayerStateAddr;
	}
	return globals::hookManager->callOriginal<decltype(&prop::functions::decreaseSupportGaugeLS)>(prop::functions::decreaseSupportGaugeLS, a1, a2, Uselessvar, NewSupportGaugeLevel);
}

__int64 __fastcall prop::functions::decreaseGuardHealth(__int64 a1, float GuardHealthSubtracted, int a3, int a4, int a5)
{
	float CurrentGuardHealth; // xmm3_4@1
	float NewGuardHealth; // xmm0_4@1

	CurrentGuardHealth = *(float*)(a1 + 8);
	if (OTraining::tcheckBox[2] == true)
	{
		NewGuardHealth = 25.0f;
	}
	else
	{
		NewGuardHealth = *(float*)(a1 + 8) - GuardHealthSubtracted;
	}
	if (NewGuardHealth == 0.0)
		NewGuardHealth = 0.0;
	if (!a3)
		*(float*)(a1 + 8) = NewGuardHealth;
	//if (Debug)	cout << endl << "PlayerAddr: " << a1 + 0x8 << endl << "Current Guard Health: " << CurrentGuardHealth << endl << "Guard Damage: " << CurrentGuardHealth - NewGuardHealth << endl << "New Guard Health: " << NewGuardHealth << endl; //Guard Health Values
	return NewGuardHealth <= 0.0 && CurrentGuardHealth <= 0.0 || a4 && NewGuardHealth <= 0.0 || a5;
}

signed __int64 __fastcall prop::functions::decreaseSubs(__int64 a1, unsigned int a2, int Uselessvar, int NewSub)
{
	if (OTraining::tcheckBox[3] == true)
	{
		signed __int64 PlayerStateAddr; // rax@1
		typedef signed __int64(__fastcall* FindPlayerAddr) (__int64 a1, unsigned int a2);
		FindPlayerAddr oFindPlayerAddr = (FindPlayerAddr)(globals::moduleBase + 0x74A71C + 0xC00);
		PlayerStateAddr = oFindPlayerAddr(a1, a2);
		if (PlayerStateAddr)
			*(float*)(PlayerStateAddr + 0x20) = 100.0f;
		return PlayerStateAddr;
	}
	return globals::hookManager->callOriginal<decltype(&prop::functions::decreaseSubs)>(prop::functions::decreaseSubs, a1, a2, Uselessvar, NewSub);
}

signed __int64 __fastcall prop::functions::decreaseTools(__int64 a1, unsigned int a2, int MaxTool, int NewTool)
{
	if (OTraining::tcheckBox[4] == true)
	{
		int NewToolCount; // ebx@1
		__int64 MaxToolCount; // rdi@1
		signed __int64 PlayerStateAddr; // rax@1

		NewToolCount = NewTool;                       // New number of each tool in each category
		MaxToolCount = MaxTool;                       // Original number of each tool in each category as loaded from duelplayerparam
		typedef signed __int64(__fastcall* FindPlayerAddr) (__int64 a1, unsigned int a2);
		FindPlayerAddr oFindPlayerAddr = (FindPlayerAddr)(globals::moduleBase + 0x74A71C + 0xC00);
		PlayerStateAddr = oFindPlayerAddr(a1, a2);
		if (PlayerStateAddr)
			*(int*)(PlayerStateAddr + 4 * MaxToolCount + 0x48) = 2;
		return PlayerStateAddr;
	}
	return globals::hookManager->callOriginal<decltype(&prop::functions::decreaseTools)>(prop::functions::decreaseTools, a1, a2, MaxTool, NewTool);
}

void __fastcall prop::functions::increaseStormGauge(__int64 BaseAddr, float Increment)
{
	float CurrentStormGauge; // xmm0_4@1
	float NewStormGauge; // xmm0_4@2

	CurrentStormGauge = *(float*)(BaseAddr + 0x34);

	if (OTraining::selectedSGItem == 1 || OTraining::selectedSGItem == 2)
	{
		if (CurrentStormGauge < 100.0)
		{
			NewStormGauge = CurrentStormGauge + Increment;
			if (OTraining::selectedSGItem == 1)
			{
				*(float*)(BaseAddr + 0x34) = 0.0f;
			}
			if (OTraining::selectedSGItem == 2)
			{
				*(float*)(BaseAddr + 0x34) = 100.0f;
			}
			if (NewStormGauge > 100.0)
				*(int*)(BaseAddr + 0x34) = 1120403456;
		}
	}
	//if (Debug)	cout << endl << "PlayerAddr: " << BaseAddr + 0x34 << endl << "Current Storm Gauge: " << CurrentStormGauge << endl << "Increment: " << Increment << endl << "New Storm Gauge: " << CurrentStormGauge + Increment << endl; //Storm Gauge Values
	if (OTraining::selectedSGItem == 0)
		globals::hookManager->callOriginal<decltype(&prop::functions::increaseStormGauge)>(prop::functions::increaseStormGauge, BaseAddr, Increment);
}