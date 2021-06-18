#ifndef MESSAGE_H 
#define MESSAGE_H
#pragma once

#include <vector>
#include <Windows.h>
#include <string>

namespace moddingApi
{
	class Message
	{
	public:
		static std::vector<std::string> MessageID;
		static std::vector<std::string> MessageStr;
		static char ViewMessageConversions;
		static uintptr_t Hook_MsgToString(uintptr_t);
		static uintptr_t Hook_MsgToString_Alt(uintptr_t);
		static char* MessageToString(char*);
		static void DoMessageInfoHook();
		static void UndoMessageInfoHook();
		static void DoMessageInfoHook2();
		static void UndoMessageInfoHook2();
	};
}

#endif