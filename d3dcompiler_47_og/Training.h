#pragma once
inline bool TrainingisOn = false;
inline const char* SGitems[]{ "Normal", "Stay at 0", "Max" };
inline int selectedSGItem = 0;
inline const char* Litems[]{ "Normal", "Unlimited", "Awakening" };
inline int selectedLItem = 0;
inline bool tcheckBox[5] = { false, false, false, false, false};
namespace training
{
	void EnableOnlineTraining();
}