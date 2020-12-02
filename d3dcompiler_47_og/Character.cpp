#include "Character.h"
#include "ccPlayer.h"
#include <iostream>
using namespace std;
using namespace moddingApi;
void Character::Initialize(uintptr_t p, uintptr_t s)
{
	int characode = ccPlayer::GetPlayerIntProperty(p, s, "characode");
	Character::SetParam1cmn(p, s, characode);

	switch (characode)
	{
		case '159':
			Character::SetParam7brt(p, s, characode);
			break;
		case '201':
			Character::SetParam7ssx(p, s, characode);
			break;
		default:
			break;
	}
}

void Character::SetParam1cmn(uintptr_t p, uintptr_t s, int characode)
{
	cout << "test" << endl;
}

void Character::SetParam7ssx(uintptr_t p, uintptr_t s, int characode)
{
	cout << "test" << endl;
}

void Character::SetParam7brt(uintptr_t p, uintptr_t s, int characode)
{
	cout << "test" << endl;
}
