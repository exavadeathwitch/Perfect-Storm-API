#include "pch.hpp"

#include "Scene.hpp"

__int64 __fastcall Scene::functions::loadccSceneNetworkSessionCreate_New(__int64 a1) {
	Scene::ccScene = "ccSceneNetworksessionCreate_New";
	return globals::hookManager->callOriginal<decltype(&Scene::functions::loadccSceneNetworkSessionCreate_New)>(Scene::functions::loadccSceneNetworkSessionCreate_New, a1);
}

__int64 __fastcall Scene::functions::loadccSceneNetworkSessionSearch_New(__int64 a1) {
	Scene::ccScene = "ccSceneNetworkSessionSearch_New";
	return globals::hookManager->callOriginal<decltype(&Scene::functions::loadccSceneNetworkSessionSearch_New)>(Scene::functions::loadccSceneNetworkSessionSearch_New, a1);
}
__int64 __fastcall Scene::functions::loadccSceneNetworkMenu_New(__int64 a1) {
	Scene::ccScene = "ccSceneNetworkMenu_New";
	return globals::hookManager->callOriginal<decltype(&Scene::functions::loadccSceneNetworkMenu_New)>(Scene::functions::loadccSceneNetworkMenu_New, a1);
}
__int64 __fastcall Scene::functions::ccSceneBootLogo(__int64 a1) {
	return globals::hookManager->callOriginal<decltype(&Scene::functions::ccSceneBootLogo)>(Scene::functions::ccSceneBootLogo, a1);
}
__int64 __fastcall Scene::functions::ccSceneTitle(__int64 a1) {
	return globals::hookManager->callOriginal<decltype(&Scene::functions::ccSceneTitle)>(Scene::functions::ccSceneTitle, a1);
}
__int64 __fastcall Scene::functions::ccSceneFreeBattle(__int64 a1) {
	return globals::hookManager->callOriginal<decltype(&Scene::functions::ccSceneFreeBattle)>(Scene::functions::ccSceneFreeBattle, a1);
}
__int64 __fastcall Scene::functions::ccSceneFreeBattleCharacterSelect(__int64 a1) {
	return globals::hookManager->callOriginal<decltype(&Scene::functions::ccSceneFreeBattleCharacterSelect)>(Scene::functions::ccSceneFreeBattleCharacterSelect, a1);
}
__int64 __fastcall Scene::functions::ChangeCore(__int64 a1) {
	//std::cout << std::hex << a1 << std::dec << std::endl;
	return globals::hookManager->callOriginal<decltype(&Scene::functions::ChangeCore)>(Scene::functions::ChangeCore, a1);
}


