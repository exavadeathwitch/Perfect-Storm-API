#pragma once

#include <stdio.h>
#include "Vector3.h"
inline bool P1isguarding = 0;
inline bool P1cantilt = 0;
inline bool P2isguarding = 0;
inline bool P2cantilt = 0;
class Character
{
	public:
	static void Character::Initialize(uintptr_t p, uintptr_t s, int P);
	static void Character::SetParam1cmn(uintptr_t p, uintptr_t s, int P);
	static void Character::SetParam7ssx(uintptr_t p, uintptr_t s, int P);
	static void Character::SetParam7brt(uintptr_t p, uintptr_t s, int P);
};

