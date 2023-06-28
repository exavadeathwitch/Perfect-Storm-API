#pragma once

#include "pch.hpp"

inline bool pressedKeys[0xFF]{ 0 };
inline bool pressedKeysPrev[0xFF]{ 0 };
class Zealot {
public:
	static std::vector<BYTE> ReadAllBytes(std::string _file) {
		std::ifstream f;
		f.open(_file);

		int FileSize = 0;
		while (!f.eof())
		{
			f.get();
			FileSize++;
		}

		f.close();
		f.open(_file, std::ios::binary);

		std::vector<BYTE> result(FileSize);

		f.seekg(0, std::ios::beg);

		for (int x = 0; x < FileSize; x++)
		{
			BYTE a = f.get();
			memcpy((void*)&result[0 + x], &a, 1);
		}

		f.close();

		return result;
	}

	static void UpdateKeys()
	{
		for (int x = 0; x < 0xFF; x++)
		{
			pressedKeysPrev[x] = pressedKeys[x];
			pressedKeys[x] = (GetKeyState(x) < 0);
		}
	}

	static bool GetKeyDown(char k)
	{
		if (pressedKeys[k] && !pressedKeysPrev[k])
			return true;
		else
			return false;
	}

	static bool GetKey(char k)
	{
		if (pressedKeys[k])
			return true;
		else
			return false;
	}

	static bool GetKeyUp(char k)
	{
		if (pressedKeysPrev[k] && !pressedKeys[k])
			return true;
		else
			return false;
	}

	static bool Hook(void* toHook, void* ourFunct, int len)
	{
		DWORD MinLen = 14;

		if (len < MinLen)
		{
			return false;
		}

		BYTE stub[] = { 0xFF, 0x25, 0x00, 0x00, 0x00, 0x00, // jmp qword ptr [$+6]
						0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 // ptr
		};

		void* pTrampoline = VirtualAlloc(0, len + sizeof(stub), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

		DWORD dwOld = 0;

		VirtualProtect(toHook, len, PAGE_EXECUTE_READWRITE, &dwOld);

		DWORD64 retto = (DWORD64)toHook + len;

		// trampoline
		memcpy(stub + 6, &retto, 8);
		memcpy((void*)((DWORD_PTR)pTrampoline), toHook, len);
		memcpy((void*)((DWORD_PTR)pTrampoline + len), stub, sizeof(stub));

		// orig
		memcpy(stub + 6, &ourFunct, 8);
		memcpy(toHook, stub, sizeof(stub));

		for (int i = MinLen; i < len; i++)
		{
			*(BYTE*)((DWORD_PTR)toHook + i) = 0x90;
		}
		VirtualProtect(toHook, len, dwOld, &dwOld);

		return true;
	}

};