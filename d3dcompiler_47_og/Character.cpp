#include "Character.h"
#include "ccPlayer.h"
#include <iostream>
#include <stdio.h>
#include "Vector3.h"
using namespace std;
using namespace moddingApi;
void Character::Initialize(uintptr_t p, uintptr_t s, int P)
{
	int characode = ccPlayer::GetPlayerIntProperty(p, s, "characode");
	Character::SetParam1cmn(p, s, P);

	switch (characode)
	{
		case '159':
			Character::SetParam7brt(p, s, P);
			break;
		case '201':
			Character::SetParam7ssx(p, s, P);
			break;
		default:
			break;
	}
}

void Character::SetParam1cmn(uintptr_t p, uintptr_t s, int P)
{
	if (ccPlayer::GetPlayerFloatProperty(p, s, "armor") < 45.0f) { ccPlayer::SetPlayerFloatProperty(p, s, "armor", 100.0f); }
	cout << "test" << endl;
}

void Character::SetParam7ssx(uintptr_t p, uintptr_t s, int P)
{
	if (P1isguarding == 1)
	{
		if ((p1buttonNumber == 34) && ((GetPlayerIntProperty(p, s, "pstate") == 10 || GetPlayerIntProperty(p, s, "pstate") == 11 || GetPlayerIntProperty(p, s, "pstate") == 12))) { SetPlayerIntProperty(p, s, "npstate", 72); SetPlayerIntProperty(p, s, "pstateflag", 1); P1isguarding = 0; }
	}
		cout << "test" << endl;
}

void Character::SetParam7brt(uintptr_t p, uintptr_t s, int P)
{
	cout << "test" << endl;
}
