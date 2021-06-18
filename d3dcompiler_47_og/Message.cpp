#include <iostream>
#include <vector>

#include "Message.h"
#include "Memory.h"

std::vector<std::string> moddingApi::Message::MessageID;
std::vector<std::string> moddingApi::Message::MessageStr;
char moddingApi::Message::ViewMessageConversions = 0;

char* moddingApi::Message::MessageToString(char* msg)
{
	typedef char* (__fastcall* message_to_string)(char*);
	message_to_string g_MessageToString;
	g_MessageToString = (message_to_string)(moddingApi::Memory::moduleBase + 0x4E89C4 + 0xC00);
	return g_MessageToString(msg);
}

uintptr_t moddingApi::Message::Hook_MsgToString(uintptr_t MessageToDecode)
{
	if (moddingApi::Message::ViewMessageConversions == 0 && strlen((char*)MessageToDecode) > 0 && *(char*)MessageToDecode != '+')
	{
		//std::cout << "og message: " << MessageToDecode << std::endl;
		moddingApi::Message::UndoMessageInfoHook();
		char* result = moddingApi::Message::MessageToString((char*)MessageToDecode);
		moddingApi::Message::DoMessageInfoHook();

		if (MessageToDecode != 0)
		{
			bool finished = false;

			std::string message((char*)MessageToDecode);

			if (finished == false)
			{
				std::string msg = (std::string)(char*)MessageToDecode;

				for (int x = 0; x < MessageID.size(); x++)
					{
						if (msg == MessageID[x])
						{
							result = (char*)MessageStr[x].c_str();
						}
					}
				if (msg != (std::string)(char*)MessageToDecode) result = (char*)msg.c_str();
			}
		}

		return (uintptr_t)result;
	}
	else
	{
		return MessageToDecode;
	}
}

typedef char* (__fastcall* message_to_string2)(char*);
message_to_string2 g_MessageToString2;

uintptr_t moddingApi::Message::Hook_MsgToString_Alt(uintptr_t MessageToDecode)
{
	g_MessageToString2 = (message_to_string2)(moddingApi::Memory::moduleBase + 0xAB4770 + 0xC00);

	if (moddingApi::Message::ViewMessageConversions == 0)
	{
		moddingApi::Message::UndoMessageInfoHook2();
		char* result = g_MessageToString2((char*)MessageToDecode);
		moddingApi::Message::DoMessageInfoHook2();

		if (MessageToDecode != 0)
		{
			bool finished = false;

			std::string msg = (std::string)(char*)MessageToDecode;
			if (finished == false)
			{
				
					for (int x = 0; x < MessageID.size(); x++)
					{
						if (msg == MessageID[x])
						{
							result = (char*)MessageStr[x].c_str();
						}
					}
			}
				if (msg != (std::string)(char*)MessageToDecode) result = (char*)msg.c_str();
		}

		return (uintptr_t)result;
	}
	else
	{
		return MessageToDecode;
	}
}
