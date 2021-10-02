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