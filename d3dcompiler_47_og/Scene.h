#ifndef SCENE_H 
#define SCENE_H
#pragma once


#include <vector>
#include <Windows.h>
#include <string>
inline std::string currentScene = "";
inline std::string prevScene = "";


namespace moddingApi
{
	class Scene
	{
	public:
		static void sceneHooks();
		static void updateSceneName(std::string newScene);
		static __int64 nLoadccSceneBootRoot(__int64 a1);
		static __int64 nLoadccSceneFreeBattleBegin(BYTE* a1);
		static __int64 nLoadccSceneBattleModeSelect(__int64 a1);
		static __int64 nLoadccSceneTitle(__int64 a1);
		static __int64 nLoadccSceneOpeningMovie(__int64 a1);
	};
}

#endif