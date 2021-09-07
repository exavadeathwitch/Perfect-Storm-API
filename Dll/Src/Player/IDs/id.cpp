#include "pch.hpp"

#include "id.hpp"

//If the character can GKunai, conditions are if the character isn't in a shuriken state
//and if the analog stick zone is equal to or greater than 2.
bool id::functions::isCanGKunai(__int64 baseAddr) {
	float analogZone = *(float*)(baseAddr + 0x1B0 + 0x70);
	__int64 partnerAddr = *(__int64*)(baseAddr + 0x1050);
	if ((*(DWORD*)(partnerAddr + 0xCC0) != 67) && (analogZone >= .2f))
		return 1;
	return 0;
}

//Checks if the character is a puppet character and if they are awakened for certain characters.
bool id::functions::isPuppetMaster(__int64 baseAddr) {
	if (*(DWORD*)(baseAddr + 0xC8C) == 0x10) //2knk
		return 1;
	if (*(DWORD*)(baseAddr + 0xC8C) == 0x1B) { //2cyb
		if (*(DWORD*)(baseAddr + 0xCBC) == 0) //if character isn't awakened
			return 1;
	}
	if (*(DWORD*)(baseAddr + 0xC8C) == 0x1E) { //2sco
		if (*(DWORD*)(baseAddr + 0xCBC) == 0) //if character isn't awakened
			return 1;
	}
	if (*(DWORD*)(baseAddr + 0xC8C) == 0x69) //1knk
		return 1;
	if (*(DWORD*)(baseAddr + 0xC8C) == 0xE3) //8knk
		return 1;
	return 0;
}