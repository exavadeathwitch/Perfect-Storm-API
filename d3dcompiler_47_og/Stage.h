#pragma once
static bool stageselected = 0;
inline int StageNumber = 10;
inline int stageisSelectedNumber = 0;
namespace Stage
{
	class stage
	{
	public:
		static int GetStageNumber();
		static void Loop();
	};
}