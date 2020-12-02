#pragma once

#include <stdio.h>
#include "Vector3.h"
class Character
{
	public:
	static void Character::Initialize(uintptr_t p, uintptr_t s);
	static void Character::SetParam1cmn(uintptr_t p, uintptr_t s, int characode);
	static void Character::SetParam7ssx(uintptr_t p, uintptr_t s, int characode);
	static void Character::SetParam7brt(uintptr_t p, uintptr_t s, int characode);
};

