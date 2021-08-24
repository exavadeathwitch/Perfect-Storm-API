#include <iostream>

#include "Scene.h"
#include "Memory.h"
#include "MinHook.h"


typedef __int64(__fastcall* loadccSceneTitle)(__int64 a1);
loadccSceneTitle oLoadccSceneTitle;

signed typedef int(__fastcall* loadccSceneBootRoot)(__int64 a1);
loadccSceneBootRoot oLoadccSceneBootRoot = NULL;

signed typedef __int64(__fastcall* loadccSceneFreeBattleBegin)(BYTE* a1);
loadccSceneFreeBattleBegin oLoadccSceneFreeBattleBegin = NULL;

signed typedef __int64(__fastcall* loadccSceneBattleModeSelect)(__int64 a1);
loadccSceneBattleModeSelect oLoadccSceneBattleModeSelect = NULL;

void moddingApi::Scene::sceneHooks() {
	bool status;
	std::uintptr_t addrLoadccSceneBootRoot = (std::uintptr_t)(moddingApi::Memory::moduleBase + 0x6E01D4 + 0xC00);
	//std::uintptr_t addrLoadccSceneBootLogo = (std::uintptr_t)(moddingApi::Memory::moduleBase + 0x6E0134 + 0xC00);
	//std::uintptr_t addrLoadccSceneAutoSaveCaution = (std::uintptr_t)(moddingApi::Memory::moduleBase + 0x6DFFF4 + 0xC00);
	//std::uintptr_t addrLoadccSceneOpeningMovie = (std::uintptr_t)(moddingApi::Memory::moduleBase + 0x6E0544 + 0xC00);
	std::uintptr_t addrLoadccSceneTitle = (std::uintptr_t)(moddingApi::Memory::moduleBase + 0x6E07C4 + 0xC00);
	//std::uintptr_t addrLoadccSceneGameModeSelect = (std::uintptr_t)(moddingApi::Memory::moduleBase + 0x6E0364 + 0xC00);
	std::uintptr_t addrLoadccSceneBattleModeSelect = (std::uintptr_t)(moddingApi::Memory::moduleBase + 0x6E0094 + 0xC00);

	status = MH_CreateHook((LPVOID)addrLoadccSceneTitle, &moddingApi::Scene::nLoadccSceneTitle, reinterpret_cast<LPVOID*>(&oLoadccSceneTitle));
	if (status != MH_OK) {
		std::cout << "could not create hook LoadccSceneTitle" << std::endl;
	}

	status = MH_EnableHook((LPVOID)addrLoadccSceneTitle);
	if (status != MH_OK) {
		std::cout << "could not enable hook LoadccSceneTitle" << std::endl;
	}

	status = MH_CreateHook((LPVOID)addrLoadccSceneBootRoot, &moddingApi::Scene::nLoadccSceneBootRoot, reinterpret_cast<LPVOID*>(&oLoadccSceneBootRoot));
	if (status != MH_OK) {
		std::cout << "could not create hook LoadccSceneTitle" << std::endl;
	}

	status = MH_EnableHook((LPVOID)addrLoadccSceneBootRoot);
	if (status != MH_OK) {
		std::cout << "could not enable hook LoadccSceneTitle" << std::endl;
	}

	status = MH_CreateHook((LPVOID)addrLoadccSceneBattleModeSelect, &moddingApi::Scene::nLoadccSceneBattleModeSelect, reinterpret_cast<LPVOID*>(&oLoadccSceneBattleModeSelect));
	if (status != MH_OK) {
		std::cout << "could not create hook LoadccSceneBattleModeSelect" << std::endl;
	}

	status = MH_EnableHook((LPVOID)addrLoadccSceneBattleModeSelect);
	if (status != MH_OK) {
		std::cout << "could not enable hook LoadccSceneBattleModeSelect" << std::endl;
	}
}

__int64 moddingApi::Scene::nLoadccSceneTitle(__int64 a1) {
	moddingApi::Scene::updateSceneName("ccSceneTitle");
	return oLoadccSceneTitle(a1);
}

void moddingApi::Scene::updateSceneName(std::string newScene) {
	prevScene = currentScene;
	currentScene = newScene;
	std::cout << "Current Scene: " << newScene << std::endl;
	std::cout << "Previous Scene: " << prevScene << std::endl;
}




//This function initializes the main boot scene
__int64 __fastcall moddingApi::Scene::nLoadccSceneBootRoot(__int64 a1) {

	BYTE* v1; // rdi@1
	__int64 v2; // rax@1
	__int64 v3; // rbx@1

	typedef __int64(__fastcall* sub_A017F0) (size_t a1);
	sub_A017F0 osub_A017F0 = (sub_A017F0)(moddingApi::Memory::moduleBase + 0xA00BF0 + 0xC00);

	typedef __int64(__fastcall* sub_8638B8) (__int64 a1);
	sub_8638B8 osub_8638B8 = (sub_8638B8)(moddingApi::Memory::moduleBase + 0x862CB8 + 0xC00);

	typedef __int64(__fastcall* sub_AB4550) (__int64 a1, BYTE* a2);
	sub_AB4550 osub_AB4550 = (sub_AB4550)(moddingApi::Memory::moduleBase + 0xAB3950 + 0xC00);

	v1 = (BYTE*)a1;
	v2 = osub_A017F0(0x128ui64);
	v3 = 0i64;
	if (v2) {
		v3 = osub_8638B8(v2);
	}
	osub_AB4550(v3, v1);
	moddingApi::Scene::updateSceneName("ccSceneBootRoot");
	return v3;
}

//This function initializes the free battle scene
__int64 __fastcall moddingApi::Scene::nLoadccSceneBattleModeSelect(__int64 a1) {

	BYTE* v1; // rdi@1
	__int64 v2; // rax@1
	__int64 v3; // rbx@1
	__int64 v4; // rax@2

	typedef __int64(__fastcall* sub_A017F0) (size_t a1);
	sub_A017F0 osub_A017F0 = (sub_A017F0)(moddingApi::Memory::moduleBase + 0xA00BF0 + 0xC00);

	typedef __int64(__fastcall* sub_6D671C) (__int64 a1);
	sub_6D671C osub_6D671C = (sub_6D671C)(moddingApi::Memory::moduleBase + 0x6D5B1C + 0xC00);

	typedef __int64(__fastcall* sub_AB4550) (__int64 a1, BYTE* a2);
	sub_AB4550 osub_AB4550 = (sub_AB4550)(moddingApi::Memory::moduleBase + 0xAB3950 + 0xC00);

	v1 = (BYTE*)a1;
	v2 = osub_A017F0(0x188ui64);
	v3 = 0i64;
	if (v2) {
		v3 = osub_6D671C(v2);
	}
	osub_AB4550(v3, v1);
	moddingApi::Scene::updateSceneName("ccSceneBattleModeSelect");
	return v3;
}

__int64 __fastcall moddingApi::Scene::nLoadccSceneFreeBattleBegin(BYTE* a1) {
	return oLoadccSceneFreeBattleBegin(a1);
}
