#include "pch.hpp"
#include "API_Console.h"

// Console Functions
std::vector<std::string> consoleCommands;
std::vector<uintptr_t> consoleFunctions;
std::vector<int> consoleParams;
void AddCommand(std::string, uintptr_t, int);
int GetCommandIndex(std::string);

void c_Help();

DWORD WINAPI moddingApi::API_Console::LoopConsole()
{
	moddingApi::API_Console::InitializeConsole();
	while (true)
	{
		std::string cmd;
		std::cout << "> ";
		std::cin >> cmd;

		moddingApi::API_Console::DoConsoleCommand(cmd);

		Sleep(100);
	}

	return 0;
}

void moddingApi::API_Console::InitializeConsole()
{
	AddCommand("Help", (uintptr_t)c_Help, 0);
	/*
	// Load plugin commands
	for (int actualPlugin = 0; actualPlugin < ccMain::PluginList.size(); actualPlugin++)
	{
		HINSTANCE hGetProcIDDLL = ccMain::PluginList.at(actualPlugin);

		typedef void(__stdcall *cmdfunct)(__int64 moduleBase, __int64 cmdFunction);
		cmdfunct funct = (cmdfunct)GetProcAddress(hGetProcIDDLL, "InitializeCommands");

		if (funct) funct(d3dcompiler_47_og::moduleBase, (__int64)AddCommand);
	}*/
}

typedef void(__stdcall * f)();
f Function;

void moddingApi::API_Console::DoConsoleCommand(std::string Input)
{
	std::string Command = Input;

	int ind = GetCommandIndex(Command);
	if (ind != -1)
	{
		Function = (f)consoleFunctions[ind];
		Function();

		std::cout << std::endl;
	}
	else
	{
		std::cout << "Command not found" << std::endl;
	}
}
/*
void c_ConvertMessage()
{
	std::string param1;

	std::cout << "MSG >> ";
	std::cin >> param1;
	char * param1_c = strcpy(new char[param1.length() + 1], param1.c_str());

	std::cout << ccGeneralGameFunctions::MessageToString(param1_c);
}

void c_ViewMessageConversions()
{
	if (ccGeneralGameFunctions::ViewMessageConversions == 0)
	{
		cout << "Enabling view of message conversions..." << endl;
		ccGeneralGameFunctions::ViewMessageConversions = 1;
	}
	else
	{
		cout << "Disabling view of message conversions..." << endl;
		ccGeneralGameFunctions::ViewMessageConversions = 0;
	}
}
*/
void c_Help()
{
	std::cout << std::endl;
	std::cout << "Available commands:" << std::endl;
	for (int x = 0; x < consoleCommands.size(); x++)
	{
		std::cout << consoleCommands[x] << std::endl;
	}
}

void moddingApi::API_Console::AddCommand(std::string command, uintptr_t function, int paramCount)
{
	consoleCommands.push_back(command);
	consoleFunctions.push_back(function);
	consoleParams.push_back(paramCount);
}

int GetCommandIndex(std::string command)
{
	int cmd = -1;

	for (int x = 0; x < consoleCommands.size(); x++)
	{
		if (command == consoleCommands[x])
		{
			cmd = x;
			x = consoleCommands.size();
		}
	}

	return cmd;
}