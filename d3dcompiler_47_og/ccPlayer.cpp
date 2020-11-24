#include "enet/enet.h"

#include <WinSock2.h>
#include <windows.h>

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

#include "ccPlayer.h"
#include "d3dcompiler_47_og.h"
#include "HookFunctions.h"
#include "ccGameProperties.h"
//#include "Input.h"
#include "LuaHook.h"
#include "ccMemoryFunctions.h"
#include "ccPlayerStruct.h"
#include "Vector3.h"
#include "ccGeneralGameFunctions.h"
#include "LuaHook_Commands.h"
#include "Memory.h"
#include "ManageMemory.h"
#pragma warning( disable: 4307 )

using namespace std;
using namespace moddingApi;
using namespace ManageMemory;
#define CHECK_BIT(var,pos) (((var)>>(pos)) & 1)
int prevFrame = 0;
int prevBattle = 0;

bool P1isguarding = 0;
bool P1cantilt = 0;

bool P2isguarding = 0;
bool P2cantilt = 0;

void ccPlayer::Start()
{
	// Currently this function does nothing.
}

__int64 __fastcall ccPlayer::meTest(__int64 a1)
{
	cout << "The function works! " << hex << a1 << endl;

	if (ccGameProperties::isOnBattle() == 1)
	{
		// Get player x info
		uintptr_t s = GetPlayerStatus(0);
		uintptr_t p = GetPlayerInfo(0);

		// If pointers are null, stop the function.
		if (s == 0 || p == 0)
		{
			cout << "Null pointers" << endl;
			return 1;
		}

		float h = GetPlayerFloatProperty(p, s, "health");
		SetPlayerFloatProperty(p, s, "health", h + 5);
		//SetPlayerFloatProperty(p, s, "modelscale", 0.5f);
	}
	else
	{
		cout << "Not on battle" << endl;
	}

	return 1;
}
float ACDStartup = 60;
// This function is ran every frame all the time.
void ccPlayer::Loop()
{
	//Setup Addresses
	
	uintptr_t baseAddr = Internal::Memory::getModule("NSUNS4.exe");
	uintptr_t basecontrollerAddr = Internal::Memory::getAddress(baseAddr + 0x016BF5A8, { 0x0, 0x8, 0x3C8, 0x5F8, 0x160 });
	
	uintptr_t P1analogAddr = basecontrollerAddr + 0x2A;
	uintptr_t P1ButtonAddr = basecontrollerAddr + 0x29;
	uintptr_t P2analogAddr = basecontrollerAddr + 0x56;
	uintptr_t P2ButtonAddr = basecontrollerAddr + 0x55;

	int p1buttonNumber = Internal::Memory::read<uint8_t>(P1ButtonAddr);
	int p1analogNumber = Internal::Memory::read<uint8_t>(P1analogAddr);
	int p2buttonNumber = Internal::Memory::read<uint8_t>(P2ButtonAddr);
	int p2analogNumber = Internal::Memory::read<uint8_t>(P2analogAddr);



	// Get keyboard keys and update their state. This is useful for using keyboard hooks, like pressing a key to do a certain function.
	/*Input::UpdateKeys();

	if (Input::GetKeyDown('U'))
	{
		cout << std::hex << GetPlayerStatus(0) << endl;
	}*/

	// If the state of isOnBattle is different, then it means we entered/quitted a battle
	if (ccGameProperties::isOnBattle() != prevBattle)
	{
		prevBattle = ccGameProperties::isOnBattle();
		if (prevBattle == 0)
		{
			// Code for when we quit a battle
			for (int x = 0; x < 6; x++)
			{
				if (x < 1)
				{
					//cout << "Exited Battle" << endl;
				}
			}
		}
		else
		{
			// Code for when we enter a battle
			for (int x = 0; x < 1; x++)
			{
				uintptr_t s = GetPlayerStatus(x);
				uintptr_t p = GetPlayerInfo(x);

				if (s != 0 && p != 0)
				{
					//int charaid = GetPlayerIntProperty(p, s, "characode");
					//InitializeCharacter(charaid, x);
					//cout << "Entered Battle" << endl;
				}
			}
		}
	}

	// If we're not in a battle, stop the code
	//cout << ccGameProperties::isOnBattle() << endl;
	if (ccGameProperties::isOnBattle() == 0) return;

	// This is the loop code for every player.
	for (int x = 0; x < 1; x++)
	{
		// Get player x info
		uintptr_t s = GetPlayerStatus(x);
		uintptr_t p = GetPlayerInfo(x);

		// Get enemy info
		uintptr_t es = GetPlayerStatus(1 - x);
		uintptr_t ep = GetPlayerInfo(1 - x);

		// Get Support Info
		uintptr_t ss1 = GetPlayerStatus(2 - x);
		uintptr_t sp1 = GetPlayerInfo(2 - x);
		uintptr_t ss2 = GetPlayerStatus(4 - x);
		uintptr_t sp2 = GetPlayerInfo(4 - x);
		uintptr_t ess1 = GetPlayerStatus(3 - x);
		uintptr_t esp1 = GetPlayerInfo(3 - x);
		uintptr_t ess2 = GetPlayerStatus(5 - x);
		uintptr_t esp2 = GetPlayerInfo(5 - x);

		// If pointers are null, stop the function.
		if (s == NULL || p == NULL) return;

		//cout << p << endl;
		float h = GetPlayerFloatProperty(p, s, "health"); // If pointers aren't null, let's check the health of the current player.

		if (h <= 0) return; // If the health is 0 or less than 0, stop the code.

		// This disables armor break
		if (GetPlayerFloatProperty(p, s, "armor") < 45.0f) { SetPlayerFloatProperty(p, s, "armor", 45.0f); }
		if (GetPlayerFloatProperty(ep, es, "armor") < 45.0f) { SetPlayerFloatProperty(ep, es, "armor", 45.0f); }
		if (GetPlayerFloatProperty(sp1, ss1, "armor") < 45.0f) { SetPlayerFloatProperty(sp1, ss1, "armor", 45.0f); }
		if (GetPlayerFloatProperty(esp1, ess1, "armor") < 45.0f) { SetPlayerFloatProperty(esp1, ess1, "armor", 45.0f); }
		if (GetPlayerFloatProperty(sp2, ss2, "armor") < 45.0f) { SetPlayerFloatProperty(sp2, ss2, "armor", 45.0f); }
		if (GetPlayerFloatProperty(esp2, ess2, "armor") < 45.0f) { SetPlayerFloatProperty(esp2, ess2, "armor", 45.0f); }

		//Better Air Dash
		if ((GetPlayerIntProperty(p, s, "pstate") == 16) && (GetPlayerIntProperty(p, s, "attackid") == 37)) { SetPlayerFloatProperty(p, s, "anmspeed", ACDStartup); }
		if (GetPlayerIntProperty(p, s, "attackid") == 38) { SetPlayerFloatProperty(p, s, "anmspeed", 1.0f); }
		if ((GetPlayerIntProperty(sp1, ss1, "pstate") == 16) && (GetPlayerIntProperty(sp1, ss1, "attackid") == 37)) { SetPlayerFloatProperty(sp1, ss1, "anmspeed", ACDStartup); }
		if (GetPlayerIntProperty(sp1, ss1, "attackid") == 38) { SetPlayerFloatProperty(sp1, ss1, "anmspeed", 1.0f); }
		if ((GetPlayerIntProperty(sp2, ss2, "pstate") == 16) && (GetPlayerIntProperty(sp2, ss2, "attackid") == 37)) { SetPlayerFloatProperty(sp2, ss2, "anmspeed", ACDStartup); }
		if (GetPlayerIntProperty(sp2, ss2, "attackid") == 38) { SetPlayerFloatProperty(sp2, ss2, "anmspeed", 1.0f); }

		//Enemy
		if ((GetPlayerIntProperty(ep, es, "pstate") == 16) && (GetPlayerIntProperty(ep, es, "attackid") == 37)) { SetPlayerFloatProperty(ep, es, "anmspeed", ACDStartup); }
		if (GetPlayerIntProperty(ep, es, "attackid") == 38) { SetPlayerFloatProperty(ep, es, "anmspeed", 1.0f); }
		if ((GetPlayerIntProperty(esp1, ess1, "pstate") == 16) && (GetPlayerIntProperty(esp1, ess1, "attackid") == 37)) { SetPlayerFloatProperty(esp1, ess1, "anmspeed", ACDStartup); }
		if (GetPlayerIntProperty(esp1, ess1, "attackid") == 38) { SetPlayerFloatProperty(esp1, ess1, "anmspeed", 1.0f); }
		if ((GetPlayerIntProperty(esp2, ess2, "pstate") == 16) && (GetPlayerIntProperty(esp2, ess2, "attackid") == 37)) { SetPlayerFloatProperty(esp2, ess2, "anmspeed", ACDStartup); }
		if (GetPlayerIntProperty(esp2, ess2, "attackid") == 38) { SetPlayerFloatProperty(esp2, ess2, "anmspeed", 1.0f); }

		//Cover Fire
		if ((GetPlayerIntProperty(p, s, "pstate") == 67) && (GetPlayerIntProperty(p, s, "attackid") == 151) && (GetPlayerIntProperty(p, s, "prevpstate") == 214)) { SetPlayerIntProperty(p, s, "npstate", 70); SetPlayerIntProperty(p, s, "pstateflag", 1); }
		if ((GetPlayerIntProperty(p, s, "pstate") == 68) && (GetPlayerIntProperty(p, s, "attackid") == 171) && (GetPlayerIntProperty(p, s, "prevpstate") == 214)) { SetPlayerIntProperty(p, s, "npstate", 71); SetPlayerIntProperty(p, s, "pstateflag", 1); }
		if ((GetPlayerIntProperty(sp1, ss1, "pstate") == 67) && (GetPlayerIntProperty(sp1, ss1, "attackid") == 151) && (GetPlayerIntProperty(sp1, ss1, "prevpstate") == 214)) { SetPlayerIntProperty(sp1, ss1, "npstate", 70); SetPlayerIntProperty(sp1, ss1, "pstateflag", 1); }
		if ((GetPlayerIntProperty(sp1, ss1, "pstate") == 68) && (GetPlayerIntProperty(sp1, ss1, "attackid") == 171) && (GetPlayerIntProperty(sp1, ss1, "prevpstate") == 214)) { SetPlayerIntProperty(sp1, ss1, "npstate", 71); SetPlayerIntProperty(sp1, ss1, "pstateflag", 1); }
		if ((GetPlayerIntProperty(sp2, ss2, "pstate") == 67) && (GetPlayerIntProperty(sp2, ss2, "attackid") == 151) && (GetPlayerIntProperty(sp2, ss2, "prevpstate") == 214)) { SetPlayerIntProperty(sp2, ss2, "npstate", 70); SetPlayerIntProperty(sp2, ss2, "pstateflag", 1); }
		if ((GetPlayerIntProperty(sp2, ss2, "pstate") == 68) && (GetPlayerIntProperty(sp2, ss2, "attackid") == 171) && (GetPlayerIntProperty(sp2, ss2, "prevpstate") == 214)) { SetPlayerIntProperty(sp2, ss2, "npstate", 71); SetPlayerIntProperty(sp2, ss2, "pstateflag", 1); }
		//Enemy
		if ((GetPlayerIntProperty(ep, es, "pstate") == 67) && (GetPlayerIntProperty(ep, es, "attackid") == 151) && (GetPlayerIntProperty(ep, es, "prevpstate") == 214)) { SetPlayerIntProperty(ep, es, "npstate", 70); SetPlayerIntProperty(ep, es, "pstateflag", 1); }
		if ((GetPlayerIntProperty(ep, es, "pstate") == 68) && (GetPlayerIntProperty(ep, es, "attackid") == 171) && (GetPlayerIntProperty(ep, es, "prevpstate") == 214)) { SetPlayerIntProperty(ep, es, "npstate", 71); SetPlayerIntProperty(ep, es, "pstateflag", 1); }
		if ((GetPlayerIntProperty(esp1, ess1, "pstate") == 67) && (GetPlayerIntProperty(esp1, ess1, "attackid") == 151) && (GetPlayerIntProperty(esp1, ess1, "prevpstate") == 214)) { SetPlayerIntProperty(esp1, ess1, "npstate", 70); SetPlayerIntProperty(esp1, ess1, "pstateflag", 1); }
		if ((GetPlayerIntProperty(esp1, ess1, "pstate") == 68) && (GetPlayerIntProperty(esp1, ess1, "attackid") == 171) && (GetPlayerIntProperty(esp1, ess1, "prevpstate") == 214)) { SetPlayerIntProperty(esp1, ess1, "npstate", 71); SetPlayerIntProperty(esp1, ess1, "pstateflag", 1); }
		if ((GetPlayerIntProperty(esp2, ess2, "pstate") == 67) && (GetPlayerIntProperty(esp2, ess2, "attackid") == 151) && (GetPlayerIntProperty(esp2, ess2, "prevpstate") == 214)) { SetPlayerIntProperty(esp2, ess2, "npstate", 70); SetPlayerIntProperty(esp2, ess2, "pstateflag", 1); }
		if ((GetPlayerIntProperty(esp2, ess2, "pstate") == 68) && (GetPlayerIntProperty(esp2, ess2, "attackid") == 171) && (GetPlayerIntProperty(esp2, ess2, "prevpstate") == 214)) { SetPlayerIntProperty(esp2, ess2, "npstate", 71); SetPlayerIntProperty(esp2, ess2, "pstateflag", 1); }

		//NM to Grab P1
		if (P1isguarding == 1)
		{
			if ((p1buttonNumber == 34) && ((GetPlayerIntProperty(p, s, "pstate") == 10 || GetPlayerIntProperty(p, s, "pstate") == 11 || GetPlayerIntProperty(p, s, "pstate") == 12))) { SetPlayerIntProperty(p, s, "npstate", 72); SetPlayerIntProperty(p, s, "pstateflag", 1); P1isguarding = 0; }	
			if ((p1buttonNumber == 34) && ((GetPlayerIntProperty(sp1, ss1, "pstate") == 10 || GetPlayerIntProperty(sp1, ss1, "pstate") == 11 || GetPlayerIntProperty(sp1, ss1, "pstate") == 12))) { SetPlayerIntProperty(sp1, ss1, "npstate", 72); SetPlayerIntProperty(sp1, ss1, "pstateflag", 1); P1isguarding = 0; }
			if ((p1buttonNumber == 34) && ((GetPlayerIntProperty(sp2, ss2, "pstate") == 10 || GetPlayerIntProperty(sp2, ss2, "pstate") == 11 || GetPlayerIntProperty(sp2, ss2, "pstate") == 12))) { SetPlayerIntProperty(sp2, ss2, "npstate", 72); SetPlayerIntProperty(sp2, ss2, "pstateflag", 1); P1isguarding = 0; }
		}
		//Side IC Tilt
		if (P1cantilt == 1)
		{
			if ((p1buttonNumber == 32) && ((GetPlayerIntProperty(p, s, "pstate") == 10 || GetPlayerIntProperty(p, s, "pstate") == 11 || GetPlayerIntProperty(p, s, "pstate") == 12))) { SetPlayerIntProperty(p, s, "npstate", 66); SetPlayerIntProperty(p, s, "pstateflag", 1); P1cantilt = 0; }
			if ((p1buttonNumber == 32) && ((GetPlayerIntProperty(sp1, ss1, "pstate") == 10 || GetPlayerIntProperty(sp1, ss1, "pstate") == 11 || GetPlayerIntProperty(sp1, ss1, "pstate") == 12))) { SetPlayerIntProperty(sp1, ss1, "npstate", 66); SetPlayerIntProperty(sp1, ss1, "pstateflag", 1); P1cantilt = 0; }
			if ((p1buttonNumber == 32) && ((GetPlayerIntProperty(sp2, ss2, "pstate") == 10 || GetPlayerIntProperty(sp2, ss2, "pstate") == 11 || GetPlayerIntProperty(sp2, ss2, "pstate") == 12))) { SetPlayerIntProperty(sp2, ss2, "npstate", 66); SetPlayerIntProperty(sp2, ss2, "pstateflag", 1); P1cantilt = 0; }
		}

		//NM to Grab P2
		if (P2isguarding == 1)
		{
			if ((p2buttonNumber == 34) && ((GetPlayerIntProperty(ep, es, "pstate") == 10 || GetPlayerIntProperty(ep, es, "pstate") == 11 || GetPlayerIntProperty(ep, es, "pstate") == 12))) { SetPlayerIntProperty(ep, es, "npstate", 72); SetPlayerIntProperty(ep, es, "pstateflag", 1); P2isguarding = 0; }
			if ((p2buttonNumber == 34) && ((GetPlayerIntProperty(esp1, ess1, "pstate") == 10 || GetPlayerIntProperty(esp1, ess1, "pstate") == 11 || GetPlayerIntProperty(esp1, ess1, "pstate") == 12))) { SetPlayerIntProperty(esp1, ess1, "npstate", 72); SetPlayerIntProperty(esp1, ess1, "pstateflag", 1); P2isguarding = 0; }
			if ((p2buttonNumber == 34) && ((GetPlayerIntProperty(esp2, ess2, "pstate") == 10 || GetPlayerIntProperty(esp2, ess2, "pstate") == 11 || GetPlayerIntProperty(esp2, ess2, "pstate") == 12))) { SetPlayerIntProperty(esp2, ess2, "npstate", 72); SetPlayerIntProperty(esp2, ess2, "pstateflag", 1); P2isguarding = 0; }
		}
		//Side IC Tilt
		if (P2cantilt == 1)
		{
			if ((p2buttonNumber == 32) && ((GetPlayerIntProperty(ep, es, "pstate") == 10 || GetPlayerIntProperty(ep, es, "pstate") == 11 || GetPlayerIntProperty(ep, es, "pstate") == 12))) { SetPlayerIntProperty(ep, es, "npstate", 66); SetPlayerIntProperty(ep, es, "pstateflag", 1); P2cantilt = 0; }
			if ((p2buttonNumber == 32) && ((GetPlayerIntProperty(esp1, ess1, "pstate") == 10 || GetPlayerIntProperty(esp1, ess1, "pstate") == 11 || GetPlayerIntProperty(esp1, ess1, "pstate") == 12))) { SetPlayerIntProperty(esp1, ess1, "npstate", 66); SetPlayerIntProperty(esp1, ess1, "pstateflag", 1); P2cantilt = 0; }
			if ((p2buttonNumber == 32) && ((GetPlayerIntProperty(esp2, ess2, "pstate") == 10 || GetPlayerIntProperty(esp2, ess2, "pstate") == 11 || GetPlayerIntProperty(esp2, ess2, "pstate") == 12))) { SetPlayerIntProperty(esp2, ess2, "npstate", 66); SetPlayerIntProperty(esp2, ess2, "pstateflag", 1); P2cantilt = 0; }
		}

		//Timers P1
		if (p1buttonNumber == 2 || p1buttonNumber == 42) { P1isguarding = 1; cout << "You can grab" << endl; }
		else
		{
			P1isguarding = 0;
		}
		if (p1analogNumber != 0) { P1cantilt = 1; cout << "You can tilt" << endl; }
		else
		{
			P1cantilt = 0;
		}

		//Timers P2
		if (p2buttonNumber == 2 || p2buttonNumber == 42) { P2isguarding = 1; cout << "You can grab" << endl; }
		else
		{
			P2isguarding = 0;
		}
		if (p2analogNumber != 0) { P2cantilt = 1; cout << "You can tilt" << endl; }
		else
		{
			P2cantilt = 0;
		}
		// Custom player code in here
		if (ccGameProperties::isOnMenu() == false && prevFrame != ccGeneralGameFunctions::GetCurrentFrame()) DoCharacterLoop(GetPlayerIntProperty(p, s, "characode"), x);
	}
	// Get next frame
	prevFrame = ccGeneralGameFunctions::GetCurrentFrame();
}

uintptr_t ccPlayer::plMain[6] = { 0, 0, 0, 0, 0, 0};
int ccPlayer::plMainId[6] = { 0, 0, 0, 0, 0, 0 };

void ccPlayer::InitializeCharacter(int c, int plNum)
{
	uintptr_t plm = 0;
	switch (c)
	{
	/*case 0x19:
	{
		ccPlayerMain_2ITC *c_2itc = (new ccPlayerMain_2ITC(plNum));
		plm = (DWORD)(c_2itc);
		plMain[plNum] = plm;
		break;
	}*/
	}
	cout << "Created pl at " << hex << plm << "\n";
}

void ccPlayer::DeleteCharacter(int c, int plNum)
{
	uintptr_t plm = plMain[plNum];
	switch (c)
	{
	/*case 0x19:
		delete &(*(ccPlayerMain_2ITC*)(plm));
		break;*/
	}
	cout << "Deleted pl at " << hex << plm << "\n";
	plMain[plNum] = 0;
}

void ccPlayer::DoCharacterLoop(int c, int plNum)
{
	uintptr_t plm = plMain[plNum];
	switch (c)
	{
	case 0x19:
		//(*(ccPlayerMain_2ITC*)(plm)).Loop(plNum);
		break;
	}
}

// This function gets the player status (health, chakra, subs...)
uintptr_t ccPlayer::GetPlayerStatus(int n)
{
	uintptr_t P1S = 0x0;
	uintptr_t EPS = 0x0;
	uintptr_t PS1S = 0x0;
	uintptr_t PS2S = 0x0;
	uintptr_t EPS1S = 0x0;
	uintptr_t EPS2S = 0x0;
	Address baseAddr = Internal::Memory::getModule("NSUNS4.exe");
	switch (n)
	{
		//Internal
		/*
		//P1
	default:
		P1S = Internal::Memory::getAddress(baseAddr + 0x016BE4B8, { 0x8, 0x8, 0x8, 0x60, 0x0, 0x38 });
		return P1S;
		//P2
	case 1:
		EPS = Internal::Memory::getAddress(baseAddr + 0x016BE4B8, { 0x8, 0x8, 0x8, 0x60, 0x90, 0x38 });
		return EPS;
		//P1 Support 1
	case 2:
		PS1S = Internal::Memory::getAddress(baseAddr + 0x016BE4B8, { 0x8, 0x8, 0x8, 0x60, 0x8, 0x38 });
		return PS1S;
		//P2 Support 1
	case 3:
		EPS1S = Internal::Memory::getAddress(baseAddr + 0x016BE4B8, { 0x8, 0x8, 0x8, 0x60, 0x98, 0x38 });
		return EPS1S;
		//P1 Support 2
	case 4:
		PS2S = Internal::Memory::getAddress(baseAddr + 0x016BE4B8, { 0x8, 0x8, 0x8, 0x60, 0x10, 0x38 });
		return PS2S;
		//P2 Support 2
	case 5:
		EPS2S = Internal::Memory::getAddress(baseAddr + 0x016BE4B8, { 0x8, 0x8, 0x8, 0x60, 0xA0, 0x38 });
		return EPS2S;
		*/
		//External
		//P1
	default:
		P1S = NSUNS4memory.getAddress(baseAddr + 0x016BE4B8, { 0x8, 0x8, 0x8, 0x60, 0x0, 0x38 });
		return P1S;
		//P2
	case 1:
		EPS = NSUNS4memory.getAddress(baseAddr + 0x016BE4B8, { 0x8, 0x8, 0x8, 0x60, 0x90, 0x38 });
		return EPS;
		//P1 Support 1
	case 2:
		PS1S = NSUNS4memory.getAddress(baseAddr + 0x016BE4B8, { 0x8, 0x8, 0x8, 0x60, 0x8, 0x38 });
		return PS1S;
		//P2 Support 1
	case 3:
		EPS1S = NSUNS4memory.getAddress(baseAddr + 0x016BE4B8, { 0x8, 0x8, 0x8, 0x60, 0x98, 0x38 });
		return EPS1S;
		//P1 Support 2
	case 4:
		PS2S = NSUNS4memory.getAddress(baseAddr + 0x016BE4B8, { 0x8, 0x8, 0x8, 0x60, 0x10, 0x38 });
		return PS2S;
		//P2 Support 2
	case 5:
		EPS2S = NSUNS4memory.getAddress(baseAddr + 0x016BE4B8, { 0x8, 0x8, 0x8, 0x60, 0xA0, 0x38 });
		return EPS2S;
	}
}

// This function gets the player info (world position, scale, speed...)
uintptr_t ccPlayer::GetPlayerInfo(int n)
{
	uintptr_t P1P = 0x0;
	uintptr_t EPP = 0x0;
	uintptr_t PS1P = 0x0;
	uintptr_t PS2P = 0x0;
	uintptr_t EPS1P = 0x0;
	uintptr_t EPS2P = 0x0;
	Address baseAddr = Internal::Memory::getModule("NSUNS4.exe");
	switch (n)
	{
		//Internal
		/*
		//P1
	default:
		P1P = Internal::Memory::getAddress(baseAddr + 0x0161C890, { 0x2F8, 0x50, 0x128, 0x68, 0x20, 0x28, 0x70 });
		return P1P;
		//P2
	case 1:
		EPP = Internal::Memory::getAddress(baseAddr + 0x0160FF60, { 0x228, 0x38, 0x70 });
		return EPP;
		//P1 Support 1
	case 2:
		PS1P = Internal::Memory::getAddress(baseAddr + 0x0160FF60, { 0x28, 0x38, 0x70 });
		return PS1P;
		//P2 Support 1
	case 3:
		EPS1P = Internal::Memory::getAddress(baseAddr + 0x0160FF60, { 0x38, 0x38, 0x70 });
		return EPS1P;
		//P1 Support 2
	case 4:
		PS2P = Internal::Memory::getAddress(baseAddr + 0x0160FF60, { 0x30, 0x38, 0x70 });
		return PS2P;
		//P2 Support 2
	case 5:
		EPS2P = Internal::Memory::getAddress(baseAddr + 0x0160FF60, { 0x40, 0x38, 0x70 });
		return EPS2P;
		*/
		//External
	default:
		P1P = NSUNS4memory.getAddress(baseAddr + 0x0161C890, { 0x2F8, 0x50, 0x128, 0x68, 0x20, 0x28, 0x70 });
		return P1P;
		//P2
	case 1:
		EPP = NSUNS4memory.getAddress(baseAddr + 0x0160FF60, { 0x228, 0x38, 0x70 });
		return EPP;
		//P1 Support 1
	case 2:
		PS1P = NSUNS4memory.getAddress(baseAddr + 0x0160FF60, { 0x28, 0x38, 0x70 });
		return PS1P;
		//P2 Support 1
	case 3:
		EPS1P = NSUNS4memory.getAddress(baseAddr + 0x0160FF60, { 0x38, 0x38, 0x70 });
		return EPS1P;
		//P1 Support 2
	case 4:
		PS2P = NSUNS4memory.getAddress(baseAddr + 0x0160FF60, { 0x30, 0x38, 0x70 });
		return PS2P;
		//P2 Support 2
	case 5:
		EPS2P = NSUNS4memory.getAddress(baseAddr + 0x0160FF60, { 0x40, 0x38, 0x70 });
		return EPS2P;
	}

}

// Given a player status pointer, get the corresponding player ID
int ccPlayer::GetPlayerStatusNumber(uintptr_t s)
{
	int n = -1;
	for (int x = 0; x < 6; x++)
	{
		if (s == ccPlayer::GetPlayerStatus(x)) n = x;
	}
	return n;
}

// Given a player info pointer, get the corresponding player ID
int ccPlayer::GetPlayerInfoNumber(uintptr_t p)
{
	int n = -1;
	for (int x = 0; x < 6; x++)
	{
		if (p == ccPlayer::GetPlayerInfo(x)) n = x;
	}
	return n;
}

// Function to use strings in a switch statement.
constexpr unsigned int str2int(const char* str, int h = 0)
{
	return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}
//IGNORE
int* ccPlayer::GetPlayerIntPointer(uintptr_t p, uintptr_t s, char* prop)
{
	int * val;

	switch (str2int(prop))
	{
	case str2int("characode"):
		val = (int*)(p + 0xC8C);
		break;
	case str2int("enablechar"):
		val = (int*)(p + 0xCA8);
		break;
	case str2int("cancontrol"):
		val = (int*)(p + 0xCAC);
		break;
	case str2int("enableanm"):
		val = (int*)(p + 0xCB0);
		break;
	case str2int("displaymdl"):
		val = (int*)(p + 0xCB8);
		break;
	case str2int("atkid"):
		val = (int*)(p + 0xCC0);
		break;
	case str2int("prevatkid"):
		val = (int*)(p + 0xCC4);
		break;
	}

	return val;
}

int ccPlayer::GetPlayerIntProperty(uintptr_t p, uintptr_t s, char* prop)
{
	int val;

	if (s == 0 || p == 0) return 0;

	switch (ccGameProperties::str2int(prop))
	{
		//Internal
		/*
	case str2int("uitem"): val = Internal::Memory::read<int>(s + 0x38); break;
	case str2int("ditem"): val = Internal::Memory::read<int>(s + 0x3C); break;
	case str2int("litem"): val = Internal::Memory::read<int>(s + 0x40); break;
	case str2int("ritem"): val = Internal::Memory::read<int>(s + 0x44); break;
	case str2int("characode"): val = Internal::Memory::read<int>(p + 0xC1C); break;
	case str2int("enablechar"): val = Internal::Memory::read<int>(p + 0xC38); break;
	case str2int("cancontrol"): val = Internal::Memory::read<int>(p + 0xC3C); break;
	case str2int("enableanm"): val = Internal::Memory::read<int>(p + 0xC40); break;
	case str2int("displaymdl"): val = Internal::Memory::read<int>(p + 0xC48); break;
	case str2int("pstate"): val = Internal::Memory::read<int>(p + 0xC50); break;
	case str2int("prevpstate"): val = Internal::Memory::read<int>(p + 0xC54); break;
	case str2int("npstate"): val = Internal::Memory::read<int>(p + 0xC58); break;
	case str2int("pstateflag"): val = Internal::Memory::read<int>(p + 0xC6C); break;
	case str2int("attackid"): val = Internal::Memory::read<int>(p + 0x1010); break;
	case str2int("prevattackid"): val = Internal::Memory::read<int>(p + 0x1024); break;
	case str2int("anmtimer"): val = Internal::Memory::read<int>(p + 0x14138); break;
	*/
	case str2int("uitem"): val = NSUNS4memory.read<int>(s + 0x38); break;
	case str2int("ditem"): val = NSUNS4memory.read<int>(s + 0x3C); break;
	case str2int("litem"): val = NSUNS4memory.read<int>(s + 0x40); break;
	case str2int("ritem"): val = NSUNS4memory.read<int>(s + 0x44); break;
	case str2int("characode"): val = NSUNS4memory.read<int>(p + 0xC1C); break;
	case str2int("enablechar"): val = NSUNS4memory.read<int>(p + 0xC38); break;
	case str2int("cancontrol"): val = NSUNS4memory.read<int>(p + 0xC3C); break;
	case str2int("enableanm"): val = NSUNS4memory.read<int>(p + 0xC40); break;
	case str2int("displaymdl"): val = NSUNS4memory.read<int>(p + 0xC48); break;
	case str2int("pstate"): val = NSUNS4memory.read<int>(p + 0xC50); break;
	case str2int("prevpstate"): val = NSUNS4memory.read<int>(p + 0xC54); break;
	case str2int("npstate"): val = NSUNS4memory.read<int>(p + 0xC58); break;
	case str2int("pstateflag"): val = NSUNS4memory.read<int>(p + 0xC6C); break;
	case str2int("attackid"): val = NSUNS4memory.read<int>(p + 0x1010); break;
	case str2int("prevattackid"): val = NSUNS4memory.read<int>(p + 0x1024); break;
	case str2int("anmtimer"): val = NSUNS4memory.read<int>(p + 0x14138); break;
	}
	return val;
}

// The function below sets a float property from the player to a specific value
void ccPlayer::SetPlayerIntProperty(uintptr_t p, uintptr_t s, char* prop, int value)
{

	if (s == 0 || p == 0) void;

	switch (ccGameProperties::str2int(prop))
	{
		//Internal
		/*
	case str2int("uitem"): Internal::Memory::write<int>(s + 0x38, value); break;
	case str2int("ditem"): Internal::Memory::write<int>(s + 0x3C, value); break;
	case str2int("litem"): Internal::Memory::write<int>(s + 0x40, value); break;
	case str2int("ritem"): Internal::Memory::write<int>(s + 0x44, value); break;
	case str2int("characode"): Internal::Memory::write<int>(p + 0xC1C, value); break;
	case str2int("enablechar"): Internal::Memory::write<int>(p + 0xC38, value); break;
	case str2int("cancontrol"): Internal::Memory::write<int>(p + 0xC3C, value); break;
	case str2int("enableanm"): Internal::Memory::write<int>(p + 0xC40, value); break;
	case str2int("displaymdl"): Internal::Memory::write<int>(p + 0xC48, value); break;
	case str2int("pstate"): Internal::Memory::write<int>(p + 0xC50, value); break;
	case str2int("prevpstate"): Internal::Memory::write<int>(p + 0xC54, value); break;
	case str2int("npstate"): Internal::Memory::write<int>(p + 0xC58, value); break;
	case str2int("pstateflag"): Internal::Memory::write<int>(p + 0xC6C, value); break;
	case str2int("attackid"): Internal::Memory::write<int>(p + 0x1010, value); break;
	case str2int("prevattackid"): Internal::Memory::write<int>(p + 0x1024, value); break;
	case str2int("anmtimer"): Internal::Memory::write<int>(p + 0x14138, value); break;
	*/
		//External
	case str2int("uitem"): NSUNS4memory.write<int>(s + 0x38, value); break;
	case str2int("ditem"): NSUNS4memory.write<int>(s + 0x3C, value); break;
	case str2int("litem"): NSUNS4memory.write<int>(s + 0x40, value); break;
	case str2int("ritem"): NSUNS4memory.write<int>(s + 0x44, value); break;
	case str2int("characode"): NSUNS4memory.write<int>(p + 0xC1C, value); break;
	case str2int("enablechar"): NSUNS4memory.write<int>(p + 0xC38, value); break;
	case str2int("cancontrol"): NSUNS4memory.write<int>(p + 0xC3C, value); break;
	case str2int("enableanm"): NSUNS4memory.write<int>(p + 0xC40, value); break;
	case str2int("displaymdl"): NSUNS4memory.write<int>(p + 0xC48, value); break;
	case str2int("pstate"): NSUNS4memory.write<int>(p + 0xC50, value); break;
	case str2int("prevpstate"): NSUNS4memory.write<int>(p + 0xC54, value); break;
	case str2int("npstate"): NSUNS4memory.write<int>(p + 0xC58, value); break;
	case str2int("pstateflag"): NSUNS4memory.write<int>(p + 0xC6C, value); break;
	case str2int("attackid"): NSUNS4memory.write<int>(p + 0x1010, value); break;
	case str2int("prevattackid"): NSUNS4memory.write<int>(p + 0x1024, value); break;
	case str2int("anmtimer"): NSUNS4memory.write<int>(p + 0x14138, value); break;
	}
}

// IGNORE
float* ccPlayer::GetPlayerFloatPointer(uintptr_t p, uintptr_t s, char* prop)
{
	float* result;

	if (s == 0 || p == 0) return 0;

	switch (ccGameProperties::str2int(prop))
	{
	case str2int("posx"): result = (float*)(p + 0x00); break;
	case str2int("posz"): result = (float*)(p + 0x04); break;
	case str2int("posy"): result = (float*)(p + 0x08); break;
	case str2int("health"): result = (float*)(s + 0x00); break;
	case str2int("maxhealth"): result = (float*)(s + 0x04); break;
	case str2int("chakra"): result = (float*)(s + 0x08); break;
	case str2int("maxchakra"): result = (float*)(s + 0x0C); break;
	case str2int("sub"): result = (float*)(s + 0x10); break;
	case str2int("maxsub"): result = (float*)(s + 0x14); break;
	case str2int("armor"): result = (float*)(s + 0x20); break;
	case str2int("maxarmor"): result = (float*)(s + 0x24); break;
	case str2int("gravity"): result = (float*)(p + 0xE8); break;
	case str2int("zmomentum"): result = (float*)(p + 0xEC); break;
	case str2int("modelscale"): result = (float*)(p + 0x190); break;
	case str2int("anmspeed"): result = (float*)(p + 0x1020); break;
	case str2int("movespeed"): result = (float*)(p + 0x14104); break;
	case str2int("guard"): result = (float*)(p + 0x149F0); break;
	case str2int("maxguard"): result = (float*)(p + 0x149F4); break;
	}

	return result;
}

// Get a float property from the player
float ccPlayer::GetPlayerFloatProperty(uintptr_t p, uintptr_t s, char* prop)
{
	float result;

	if (s == 0 || p == 0) return 0;

	switch (ccGameProperties::str2int(prop))
	{
		/*
		//Internal
	case str2int("posx"): result = Internal::Memory::read<float>(p + 0x00); break;
	case str2int("posy"): result = Internal::Memory::read<float>(p + 0x04); break;
	case str2int("posz"): result = Internal::Memory::read<float>(p + 0x08); break;
	case str2int("health"): result = Internal::Memory::read<float>(s + 0x00); break;
	case str2int("maxhealth"): result = Internal::Memory::read<float>(s + 0x04); break;
	case str2int("chakra"): result = Internal::Memory::read<float>(s + 0x08); break;
	case str2int("maxchakra"): result = Internal::Memory::read<float>(s + 0x0C); break;
	case str2int("sub"): result = Internal::Memory::read<float>(s + 0x10); break;
	case str2int("maxsub"): result = Internal::Memory::read<float>(s + 0x14); break;
	case str2int("armor"): result = Internal::Memory::read<float>(s + 0x20); break;
	case str2int("maxarmor"): result = Internal::Memory::read<float>(s + 0x24); break;
	case str2int("gravity"): result = Internal::Memory::read<float>(p + 0xE8); break;
	case str2int("zmomentum"): result = Internal::Memory::read<float>(p + 0xEC); break;
	case str2int("modelscale"): result = Internal::Memory::read<float>(p + 0x20); break;
	case str2int("anmspeed"): result = Internal::Memory::read<float>(p + 0x1020); break;
	case str2int("movespeed"): result = Internal::Memory::read<float>(p + 0x14104); break;
	case str2int("guard"): result = Internal::Memory::read<float>(p + 0x149F0); break;
	case str2int("maxguard"): result = Internal::Memory::read<float>(p + 0x149F4); break;
	*/

		
		//External
	case str2int("posx"): result = NSUNS4memory.read<float>(p + 0x00); break;
	case str2int("posy"): result = NSUNS4memory.read<float>(p + 0x04); break;
	case str2int("posz"): result = NSUNS4memory.read<float>(p + 0x08); break;
	case str2int("health"): result = NSUNS4memory.read<float>(s + 0x00); break;
	case str2int("maxhealth"): result = NSUNS4memory. read<float>(s + 0x04); break;
	case str2int("chakra"): result = NSUNS4memory.read<float>(s + 0x08); break;
	case str2int("maxchakra"): result = NSUNS4memory.read<float>(s + 0x0C); break;
	case str2int("sub"): result = NSUNS4memory.read<float>(s + 0x10); break;
	case str2int("maxsub"): result = NSUNS4memory.read<float>(s + 0x14); break;
	case str2int("armor"): result = NSUNS4memory.read<float>(s + 0x20); break;
	case str2int("maxarmor"): result = NSUNS4memory.read<float>(s + 0x24); break;
	case str2int("gravity"): result = NSUNS4memory.read<float>(p + 0xE8); break;
	case str2int("zmomentum"): result = NSUNS4memory.read<float>(p + 0xEC); break;
	case str2int("modelscale"): result = NSUNS4memory.read<float>(p + 0x20); break;
	case str2int("anmspeed"): result = NSUNS4memory.read<float>(p + 0x1020); break;
	case str2int("movespeed"): result = NSUNS4memory.read<float>(p + 0x14104); break;
	case str2int("guard"): result = NSUNS4memory.read<float>(p + 0x149F0); break;
	case str2int("maxguard"): result = NSUNS4memory.read<float>(p + 0x149F4); break;
	
	}

	return result;
}

// The function below sets a float property from the player to a specific value
void ccPlayer::SetPlayerFloatProperty(uintptr_t p, uintptr_t s, char* prop, float value)
{

	if (s == 0 || p == 0) void;
	switch (ccGameProperties::str2int(prop))
	{
	/* 
	//Internal
	case str2int("posx"): Internal::Memory::write<float>(p + 0x00, value); break;
	case str2int("posy"): Internal::Memory::write<float>(p + 0x04, value); break;
	case str2int("posz"): Internal::Memory::write<float>(p + 0x08, value); break;
	case str2int("health"): Internal::Memory::write<float>(s + 0x00, value); break;
	case str2int("maxhealth"): Internal::Memory::write<float>(s + 0x04, value); break;
	case str2int("chakra"): Internal::Memory::write<float>(s + 0x08, value); break;
	case str2int("maxchakra"): Internal::Memory::write<float>(s + 0x0C, value); break;
	case str2int("sub"): Internal::Memory::write<float>(s + 0x10, value); break;
	case str2int("maxsub"): Internal::Memory::write<float>(s + 0x14, value); break;
	case str2int("armor"): Internal::Memory::write<float>(s + 0x20, value); break;
	case str2int("maxarmor"): Internal::Memory::write<float>(s + 0x24, value); break;
	case str2int("gravity"): Internal::Memory::write<float>(p + 0xE8, value); break;
	case str2int("zmomentum"): Internal::Memory::write<float >(p + 0xEC, value); break;
	case str2int("modelscale"): Internal::Memory::write<float>(p + 0x20, value); break;
	case str2int("anmspeed"): Internal::Memory::write<float>(p + 0x1020, value); break;
	case str2int("movespeed"): Internal::Memory::write<float>(p + 0x14104, value); break;
	case str2int("guard"): Internal::Memory::write<float>(p + 0x149F0, value); break;
	case str2int("maxguard"): Internal::Memory::write<float>(p + 0x149F4, value); break;
	*/
	//External
	case str2int("posx"): NSUNS4memory.write<float>(p + 0x00, value); break;
	case str2int("posy"): NSUNS4memory.write<float>(p + 0x04, value); break;
	case str2int("posz"): NSUNS4memory.write<float>(p + 0x08, value); break;
	case str2int("health"): NSUNS4memory.write<float>(s + 0x00, value); break;
	case str2int("maxhealth"): NSUNS4memory.write<float>(s + 0x04, value); break;
	case str2int("chakra"): NSUNS4memory.write<float>(s + 0x08, value); break;
	case str2int("maxchakra"): NSUNS4memory.write<float>(s + 0x0C, value); break;
	case str2int("sub"): NSUNS4memory.write<float>(s + 0x10, value); break;
	case str2int("maxsub"): NSUNS4memory.write<float>(s + 0x14, value); break;
	case str2int("armor"): NSUNS4memory.write<float>(s + 0x20, value); break;
	case str2int("maxarmor"): NSUNS4memory.write<float>(s + 0x24, value); break;
	case str2int("gravity"): NSUNS4memory.write<float>(p + 0xE8, value); break;
	case str2int("zmomentum"): NSUNS4memory.write<float >(p + 0xEC, value); break;
	case str2int("modelscale"): NSUNS4memory.write<float>(p + 0x20, value); break;
	case str2int("anmspeed"): NSUNS4memory.write<float>(p + 0x1020, value); break;
	case str2int("movespeed"): NSUNS4memory.write<float>(p + 0x14104, value); break;
	case str2int("guard"): NSUNS4memory.write<float>(p + 0x149F0, value); break;
	case str2int("maxguard"): NSUNS4memory.write<float>(p + 0x149F4, value); break;

	}
}

// Gets the player position in a Vector3
Vector3 ccPlayer::GetPlayerPosition(uintptr_t p, uintptr_t s)
{
	return Vector3
	(
		GetPlayerFloatProperty(p, s, "posx"),
		GetPlayerFloatProperty(p, s, "posy"),
		GetPlayerFloatProperty(p, s, "posz")
	);
}

// Calculates the distance between two given players
float ccPlayer::GetPlayerDistance(uintptr_t p, uintptr_t s, uintptr_t ep, uintptr_t es)
{
	return 0;
	//return Vector3::Distance(GetPlayerPosition(p, s), GetPlayerPosition(ep, es));
}