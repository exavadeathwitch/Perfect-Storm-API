#include <iostream>
#include <string>
#include <stdio.h>
#include <filesystem>
#include <vector>

#include "Main.h"
#include "Console.h"
#include "Settings.h"
#include "Memory.h"
#include "minGlue.h"
#include "minIni.h"
#include "MinHook.h"
#include "Music.h"
#include "SDL2/SDL2Music.h"

std::vector<const char*> moddingApi::Settings::CpkToLoad;
std::vector<int> moddingApi::Settings::CpkPriority;

#define sizearray(a)  (sizeof(a) / sizeof((a)[0]))

void moddingApi::Settings::ReadConfig(char *ConfigPath) {
	


	bool EnableConsole = ini_getl("General", "Console", -1, ConfigPath);
	if (EnableConsole) {
		//moddingApi::Console::InitConsole();
		moddingApi::EnableConsole = 1;
	}
	
	char GameVer[100];
	ini_gets("General", "Version", "dummy", GameVer, sizearray(GameVer), ConfigPath);
	if (strcmp(GameVer, "Default") == 0) {
		moddingApi::EnablePerfectStorm = 0;
	}
	
	if (strcmp(GameVer, "Enhanced") == 0) {
		std::cout << "Enhanced Enabled!" << std::endl;
		moddingApi::EnablePerfectStorm = 1;
	}
	moddingApi::Memory::InitHooks();

	if (strcmp(GameVer, "Default") != 0) {
		moddingApi::EnablePerfectStorm = 2;
		std::cout << "Perfect Storm Enabled!" << std::endl;
	}
	std::cout << moddingApi::EnablePerfectStorm << std::endl;
	moddingApi::Settings::AddCpk();

	bool EnableUpdater = ini_getl("General", "Auto-Updater", -1, ConfigPath);
	if (EnableUpdater && (moddingApi::EnablePerfectStorm != 0)) {
		std::cout << "Auto-Updater Enabled!" << std::endl;
	}
	moddingApi::Memory::WriteBytes();
}

typedef int(__fastcall* updateSettings)(__int64 a1);
updateSettings oUpdateSettings = NULL;

int __fastcall nUpdateSettings(__int64 a1) {

	int retval = oUpdateSettings(a1);
	musicVol = *(int8_t*)(moddingApi::Memory::moduleBase + 0x161FEEA);
	std::cout << "volume" << musicVol << std::endl;
	Mix_VolumeMusic(musicVol*.8);
	return retval;
}


void moddingApi::Settings::settingsHooks() {
	std::uintptr_t addrUpdateSettings = (std::uintptr_t)(moddingApi::Memory::moduleBase + 0x6A9210 + 0xC00);
	bool status;
	status = MH_CreateHook((LPVOID)addrUpdateSettings, nUpdateSettings, (LPVOID*)(&oUpdateSettings));
	if (status != MH_OK)
	{
		std::cout << "could not create hook Update Settings" << std::endl;
	}

	status = MH_EnableHook((LPVOID)addrUpdateSettings);
	if (status != MH_OK)
	{
		std::cout << "could not enable hook Update Settings" << std::endl;
	}

}
void moddingApi::Settings::AddCpk() {
	int priority = 14;
	char* CpkPath = strcpy(new char[moddingApi::Main::GetStormDirectory().length() + 1], moddingApi::Main::GetStormDirectory().c_str());
	strcat(CpkPath, "\\PSAPI\\");
	switch (moddingApi::EnablePerfectStorm) {
	case 1: strcat(CpkPath, "Enhanced.cpk");
		break;
	case 2: std::cout << CpkPath << std::endl; 
		strcat(CpkPath, "PerfectStorm.cpk");
		break;
	default: std::cout << CpkPath << std::endl;
	}

	moddingApi::Settings::CpkToLoad.push_back(CpkPath);
	moddingApi::Settings::CpkPriority.push_back(priority);
}

int moddingApi::Settings::LoadCpkInitial()
{
	__int64 v0; // rax@1
	__int64 v1; // rbx@1
	unsigned int ActualVersion; // eax@3
	unsigned int GameVersion; // ebx@3
	__int64 v4; // rbx@5
	signed __int64 v5; // rdi@5
	const char* v6; // rax@10
	void* v7; // rdx@13
	void* v8; // rbx@16
	int v9; // eax@16
	//const char *v11; // [sp+20h] [bp-188h]@12
	//int v12; // [sp+28h] [bp-180h]@12
	void* Memory; // [sp+30h] [bp-178h]@5
	int v14; // [sp+38h] [bp-170h]@5
	const char* v15; // [sp+40h] [bp-168h]@5
	unsigned __int64 v16; // [sp+48h] [bp-160h]@5
	const char* v17; // [sp+50h] [bp-158h]@5
	int v18; // [sp+58h] [bp-150h]@5
	const char* v19; // [sp+60h] [bp-148h]@5
	int v20; // [sp+68h] [bp-140h]@5
	const char* v21; // [sp+70h] [bp-138h]@5
	int v22; // [sp+78h] [bp-130h]@5
	const char* v23; // [sp+80h] [bp-128h]@5
	int v24; // [sp+88h] [bp-120h]@5
	__int64* v25; // [sp+90h] [bp-118h]@4
	signed int v26; // [sp+98h] [bp-110h]@4
	__int64 v27; // [sp+A0h] [bp-108h]@4
	__int64 retaddr; // [sp+1A8h] [bp+0h]@1

	v0 = (__int64)&retaddr;
	v1 = moddingApi::Memory::GetQword(0x1416663C8);
	if (!v1) return v0;

	if (moddingApi::Memory::GetDword(0x1415F8244) != 1)
	{
		// 0x1CD368 addstring to buffer
		typedef signed __int64(__fastcall* fc_AddStringToBuffer)(__int64 a, __int64 b);
		fc_AddStringToBuffer AddStringToBuffer = (fc_AddStringToBuffer)(moddingApi::Memory::moduleBase + 0x1CD368 + 0xC00);
		AddStringToBuffer((__int64)&Memory, moddingApi::Memory::GetOffset(0x1557E58));
		v7 = &Memory;

		if (v16 >= 0x10)
			v7 = Memory;

		// 0xA470F0
		typedef int(__fastcall* sub_140A47CF0)(__int64 a, __int64 b);
		sub_140A47CF0 sub_140A47CF0_f = (sub_140A47CF0)(moddingApi::Memory::moduleBase + 0xA470F0 + 0xC00);
		v0 = sub_140A47CF0_f(v1, (__int64)v7);

		if (v16 >= 0x10)
		{
			v8 = Memory;

			typedef int(__fastcall* sub_140A01D60)(__int64 a);
			sub_140A01D60 sub_140A01D60_f = (sub_140A01D60)(moddingApi::Memory::moduleBase + 0xA01160 + 0xC00);
			v9 = sub_140A01D60_f((__int64)&v17);

			// 0xA01080
			typedef signed __int64(__fastcall* nuccMemoryType__Function01)(__int64 a);
			nuccMemoryType__Function01 nuccMemoryType__Function01_f = (nuccMemoryType__Function01)(moddingApi::Memory::moduleBase + 0xA01080 + 0xC00);
			nuccMemoryType__Function01(v9);

			// 0xA00EA0
			typedef void(__fastcall* sub_140A01AA0)(__int64 a);
			sub_140A01AA0 sub_140A01AA0_f = (sub_140A01AA0)(moddingApi::Memory::moduleBase + 0xA00EA0 + 0xC00);
			sub_140A01AA0(v8);

			// 0xA01050
			typedef signed __int64(__fastcall* nuccMemoryUnknown__PopCurrent)();
			nuccMemoryUnknown__PopCurrent nuccMemoryUnknown__PopCurrent_f = (nuccMemoryUnknown__PopCurrent)(moddingApi::Memory::moduleBase + 0xA01050 + 0xC00);
			v0 = nuccMemoryUnknown__PopCurrent_f();

		}
		goto LABEL_17;
	}

	// LOAD PATCH
	{
		ActualVersion = 11;
		GameVersion = ActualVersion;
		cpkdata* c = (cpkdata*)malloc(sizeof(cpkdata));

		c->path = "sim:data/patch/12/launch.cpk";
		c->priority = 1;

		typedef signed __int64(__fastcall* sub_14056C3D4)(__int64 a, __int64 b);
		sub_14056C3D4 sub_14056C3D4_f = (sub_14056C3D4)(moddingApi::Memory::moduleBase + 0x56B7D4 + 0xC00);
		sub_14056C3D4_f((__int64)c, GameVersion);
	}

	// LOAD BASE GAME CPK
	{
		std::vector<const char*> cpks;
		std::vector<int> priority;
		cpks.push_back("sim:data/launch/data1.cpk");
		priority.push_back(1);
		cpks.push_back("sim:data/launch/stage1.cpk");
		priority.push_back(1);
		cpks.push_back("disc:data/launch/dataRegion.cpk");
		priority.push_back(1);
		cpks.push_back("sim:data/launch/sound.cpk");
		priority.push_back(0);
		cpks.push_back("disc:data/launch/adx2.cpk");
		priority.push_back(0);
		cpks.push_back("disc:data/launch/movie1.cpk");
		priority.push_back(0);

		v5 = cpks.size();

		int x = 0;
		cpkdata* c = (cpkdata*)malloc(sizeof(cpkdata));

		do
		{
			// 0x56B74C
			typedef signed __int64(__fastcall* sub_14056C34C)(__int64 a);
			sub_14056C34C sub_14056C34C_f = (sub_14056C34C)(moddingApi::Memory::moduleBase + 0x56B74C + 0xC00);

			c->path = cpks.at(x);
			c->priority = priority.at(x);

			v0 = sub_14056C34C_f((__int64)c);
			x++;
			--v5;
		} while (v5);
	}

	int region = *(int*)(moddingApi::Memory::GetQword(0x1416663C8) + 0x1D4);
	//cout << "Game region is: " << region << endl;

	if (region != 1)
	{
		switch (region)
		{
		default:
		{
			std::cout << "ERROR LOADING LANGUAGE :: REGION ID IS " << std::hex << region << "! REPORT ERROR TO EXAVADEATHWITCH" << std::endl;

			if (!moddingApi::Memory::GetQword(0x1416759C8))
				goto LABEL_17;

			// 0xA31EB0
			typedef signed __int64(__fastcall* sub_140A32AB0)(__int64 a, __int64 b, __int64 c);
			sub_140A32AB0 sub_140A32AB0_f = (sub_140A32AB0)(moddingApi::Memory::moduleBase + 0xA31EB0 + 0xC00);
			sub_140A32AB0_f(moddingApi::Memory::GetQword(0x1416759C8), (__int64)"disc:data/launch/LANG/dataRegion.cpk", (__int64)&v27);

			v6 = (const char*)&v27;
		}
		break;
		case 0x2:
			v6 = "disc:data/launch/fre/dataRegion.cpk";
			break;
		case 0x3:
			v6 = "disc:data/launch/spa/dataRegion.cpk";
			break;
		case 0x4:
			v6 = "disc:data/launch/ger/dataRegion.cpk";
			break;
		case 0x5:
			v6 = "disc:data/launch/ita/dataRegion.cpk";
			break;
		case 0x8:
			v6 = "disc:data/launch/rus/dataRegion.cpk";
			break;
		case 0x9:
			v6 = "disc:data/launch/kokr/dataRegion.cpk";
			break;
		case 0xA:
			v6 = "disc:data/launch/chi/dataRegion.cpk";
			break;
		case 0x10:
			v6 = "disc:data/launch/por/dataRegion.cpk";
			break;
		case 0x12:
			v6 = "disc:data/launch/pol/dataRegion.cpk";
			break;
		case 0x13:
			v6 = "disc:data/launch/spa/dataRegion.cpk";
			break;
		case 0x14:
			v6 = "disc:data/launch/arae/dataRegion.cpk";
			break;
		}

		cpkdata* c = (cpkdata*)malloc(sizeof(cpkdata));
		c->path = v6;
		c->priority = 1;

		typedef signed __int64(__fastcall* sub_14056C34C)(__int64 a);
		sub_14056C34C sub_14056C34C_f = (sub_14056C34C)(moddingApi::Memory::moduleBase + 0x56B74C + 0xC00);
		v0 = sub_14056C34C_f((__int64)c);
	}

LABEL_17:
	// LOAD CUSTOM CPK
	{
		cpkdata* c = (cpkdata*)malloc(sizeof(cpkdata));

		for (int x = 0; x < CpkToLoad.size(); x++)
		{
			typedef signed __int64(__fastcall* sub_14056C34C)(__int64 a);
			sub_14056C34C sub_14056C34C_f = (sub_14056C34C)(moddingApi::Memory::moduleBase + 0x56B74C + 0xC00);

			GameVersion = CpkPriority.at(x);
			//std::cout << "Loaded cpk " << CpkToLoad.at(x) << std::endl;
			c->path = CpkToLoad.at(x);
			c->priority = 0;

			typedef signed __int64(__fastcall* sub_14056C3D4)(__int64 a, __int64 b);
			sub_14056C3D4 sub_14056C3D4_f = (sub_14056C3D4)(moddingApi::Memory::moduleBase + 0x56B7D4 + 0xC00);
			sub_14056C3D4_f((__int64)c, GameVersion);
		}
	}

	if (moddingApi::Memory::GetQword(0x1415F8298))
	{
		//v11 = (const char *)1001;
		//v12 = 1003;

		// 0x56B284
		typedef signed __int64(__fastcall* sub_14056BE84)(__int64 a);
		sub_14056BE84 sub_14056BE84_f = (sub_14056BE84)(moddingApi::Memory::moduleBase + 0x56B284 + 0xC00);
		v0 = sub_14056BE84_f(moddingApi::Memory::GetQword(0x1415F8298));
	}

	return v0;
}