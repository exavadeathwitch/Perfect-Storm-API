#pragma once

#include "pch.hpp"

namespace S1API {

	class gamepad {
	public:
		static int __fastcall gamepadLoop(__int64 a1);
		static signed __int64 __fastcall getPadAddr(__int64 a1, signed int padNum, int a3);
	};
	class pad {
	public:
		DWORD padNum = 420;
		DWORD enabled = -1;
		DWORD nothing1;
		DWORD nothing2;
		DWORD InstantInput;
		DWORD ReleaseInput;
		DWORD HeldInput;
		DWORD nothing31;
		DWORD nothing32;
		DWORD nothing33;
		DWORD nothing34;
		DWORD nothing35;
		DWORD nothing36;
		DWORD nothing3;
		DWORD nothing4;
		DWORD nothing5;
		DWORD nothing6;
		DWORD nothing7;
		DWORD nothing8;
		DWORD nothing9;
		DWORD nothing10;
		DWORD nothing11;
		DWORD nothing12;
		DWORD nothing13;
	};
	inline pad dummypad; //This is used to allocate pads that I don't want to get inputs from
	inline pad hostpad; //This is used to store inputs from a host sending to client. Used for client.
	inline pad clientpad; //This is used to store inputs from a client connecting to a host. Used for host.
}