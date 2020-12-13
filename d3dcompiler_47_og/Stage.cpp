#include "Stage.h"
#include "ccGameProperties.h"
#include "Memory.h"
#include "ManageMemory.h"
#include "SDL2/SDL2Music.h"
using namespace Stage;
using namespace moddingApi;
using namespace std;
//This function gets the selected stage
int stage::GetStageNumber()
{
	int n;
	// cout << "ccGameProperties::isOnMenu: " << ccGameProperties::isOnMenu() << endl;
	// cout << "ccGameProperties::isOnStageSelect: " << ccGameProperties::isOnStageSelect() << endl;
	// cout << "stageselected: " << stageselected << endl;
	if (ccGameProperties::isOnMenu() == 1 && ccGameProperties::isOnStageSelect() == 1)
	{
		stageselected = 0;
	}
	if (ccGameProperties::isOnMenu() == 1 && ccGameProperties::isOnStageSelect() == 1 && stageselected == 0)
	{
		uintptr_t baseAddr = Internal::Memory::getModule("NSUNS4.exe");
		uintptr_t stageNumberAddr = Internal::Memory::getAddress(baseAddr + 0x016BDA18, { 0x90, 0x128, 0x50, 0x18 });
		uintptr_t stageisSelectedAddr = stageNumberAddr + 0x4;
		int stageNumber = Internal::Memory::read<uint8_t>(stageNumberAddr);
		stageisSelectedNumber = Internal::Memory::read<uint8_t>(stageisSelectedAddr);
		std::cout << "StageNumber: " << stageNumber << std::endl;
		std::cout << "Stage is selected: " << stageisSelectedNumber << std::endl;
		if (stageisSelectedNumber == 1)
		{
			n = stageNumber;
			StageNumber = n;
			stageselected = 1;
		}
	}
	return n;
}
//This function loops a bit faster than every frame.
void stage::Loop()
{
	stage::GetStageNumber();
	// std::cout << "StageNumber: " << StageNumber << std::endl;
	if (ccGameProperties::getCurrentTrack() == 4)
	{
		SDL2Music music;
		music.Halt_Music();
	}
}