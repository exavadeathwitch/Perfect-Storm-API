#pragma once

#include <stdio.h>
#include <windows.h>

using namespace std;

namespace moddingApi
{
	class ccPlayer
	{
	public:
		static int AfterCharacterCollision(uintptr_t);

		static BYTE CtrlBytes[15];
		static int Ctrl(uintptr_t, uintptr_t);
		static void DoCtrlHook();
		static void UndoCtrlHook();

		static void DoMovementHook();
		static void UndoMovementHook();

		// Awakening funtions:
		static BYTE OriginalAwakeningFunction[20];
		//static bool AwakeDebugEnabled;
	};
}