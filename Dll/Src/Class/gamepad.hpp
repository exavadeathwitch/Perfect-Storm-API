#pragma once

#include "pch.hpp"

class pad {
public:
	DWORD padNum; //0-3
	DWORD enabled; //0 or 1
	DWORD nothing1;
	DWORD nothing2;
	DWORD InstantInput;
	DWORD ReleaseInput;
	DWORD HeldInput;
	DWORD nothing31;
	DWORD nothing32;
	DWORD nothing33;
	short leftanalogup;
	short leftanalogdown;
	short leftanalogleft;
	short leftanalogright;
	short rightanalogup;
	short rightanalogdown;
	short rightanalogleft;
	short rightanalogright;
	DWORD nothing4;
	DWORD nothing5;
	DWORD nothing6;
	DWORD nothing7;
	DWORD nothing8;
	short lefttriggerpressed;
	short righttriggerpressed;
	DWORD nothing10;
	DWORD nothing11;
	DWORD nothing12;
	DWORD nothing13; //96 length dec for class
};

class playerpadanalog {
public:
	short leftanalogup;
	short leftanalogdown;
	short leftanalogleft;
	short leftanalogright;
	short rightanalogup;
	short rightanalogdown;
	short rightanalogleft;
	short rightanalogright;
};