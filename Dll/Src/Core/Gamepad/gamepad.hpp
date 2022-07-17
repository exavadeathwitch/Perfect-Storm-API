#pragma once

#include "pch.hpp"
#include "imgui/include/imgui.h"
namespace S1API {
	inline bool disablepad0;
	inline bool disablepad1;
	class gamepad {
	public:
		static int __fastcall gamepadLoop(__int64 a1);
		static signed __int64 __fastcall getPadAddr(__int64 a1, signed int padNum, int a3);
		static void decodeinputpacket();
	};
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
	inline pad dummypad; //This is used to allocate pads that I don't want to get inputs from
	inline pad hostpad; //This is used to store inputs from a host sending to client. Used for client.
	inline pad clientpad; //This is used to store inputs from a client connecting to a host. Used for host.
}