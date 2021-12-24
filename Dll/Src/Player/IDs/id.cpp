#include "pch.hpp"

#include "id.hpp"

#include "Player/Mechanics/mech.hpp"
//If the character can GKunai, conditions are if the character isn't in a shuriken state
//and if the analog stick zone is equal to or greater than 2.
bool id::functions::isCanGKunai(__int64 baseAddr) {
	float analogZone = *(float*)(baseAddr + 0x1B0 + 0x70);
	__int64 partnerAddr = *(__int64*)(baseAddr + 0x1050);
	if ((*(DWORD*)(partnerAddr + 0xCC0) != 67) && (analogZone >= .2f))
		return 1;
	return 0;
}
/// <summary>
/// Returns a boolean depending on if the character is in G-Kunai or not.
/// </summary>
/// <param name="baseAddr"></param>
/// <returns>Whether the character is in G-Kunai or not.</returns>
bool id::functions::isInGKunai(__int64 baseAddr) {
	__int64 partnerAddr = 0;
	__int64 partnerState = 0;
	__int64 prevPartnerState = 0;
	if (!id::functions::isPuppetMaster(baseAddr))
		return 0;
	else {
		partnerAddr = *(__int64*)(baseAddr + 0x1050);
		partnerState = *(DWORD*)(partnerAddr + 0xCC0);
		prevPartnerState = *(DWORD*)(partnerAddr + 0xCC4);
	}
	std::cout << partnerState << std::endl;
	std::cout << prevPartnerState << std::endl;
	if (partnerState == 67 && (prevPartnerState == 233 || prevPartnerState == 235))
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

//Checks if the character is a partner character.
bool id::functions::isPartnerCharacter(__int64 baseAddr) {
	if (*(DWORD*)(baseAddr + 0xC8C) == 0x0) //No characode, 5mdr limbo clones
		return 1;
	if (*(DWORD*)(baseAddr + 0xC8C) == 0x29) //2akm
		return 1;
	if (*(DWORD*)(baseAddr + 0xC8C) == 0x2A) //2krs
		return 1;
	if (*(DWORD*)(baseAddr + 0xC8C) == 0x2B) //2par
		return 1;
	if (*(DWORD*)(baseAddr + 0xC8C) == 0x2C) //2kkg
		return 1;
	if (*(DWORD*)(baseAddr + 0xC8C) == 0x66) //1akm
		return 1;
	if (*(DWORD*)(baseAddr + 0xC8C) == 0x6A) //1krs
		return 1;
	if (*(DWORD*)(baseAddr + 0xC8C) == 0xE6) //8aem
		return 1;
	return 0;
}

__int64 id::functions::getHealthAddr(__int64 baseAddr) {
	__int64 v2; // rdi@1
	__int64 v4; // rdi@2
	int v5; // eax@3

	v2 = *(__int64*)(globals::moduleBase + 0x161C8C8);
	v4 = 104i64 * (*(int(__fastcall**)(__int64))(*(__int64*)baseAddr + 64i64))(baseAddr) + v2 + 0x18;
	v5 = (*(int(__fastcall**)(signed __int64))(*(__int64*)(baseAddr + 2816) + 32i64))(baseAddr + 2816);
	
	typedef signed __int64(__fastcall* FindPlayerAddr) (__int64 a1, unsigned int a2);
	FindPlayerAddr oFindPlayerAddr = (FindPlayerAddr)(globals::moduleBase + 0x74A71C + 0xC00);

	return oFindPlayerAddr(v4, v5);
}

/// <summary>
/// Returns an int based off of the type of awakening.
/// </summary>
/// <param name="baseAddr"></param>
/// <returns>0 for no model change, 1 for model change, 2 for big bod, 5 for n/a.</returns>
int id::functions::awakeningType(__int64 baseAddr) {

	DWORD characterID = *(DWORD*)(baseAddr + 0xC8C);
		switch (characterID) {
		case 0x0: return 5;	break;		//Nothing
		default: return 5; break;		//Default case
	}
}