#include "Controls.h"
#include "Memory.h"
#include "ManageMemory.h"
#include <iostream>
#include <Windows.h>
#include <Xinput.h>
using namespace Controls;
bool APress = 0;
bool AHold = 0;
bool ARelease = 0;
using std::cout;
using std::endl;
class Gamepad
{
private:
	int cId;
	XINPUT_STATE state;

	float deadzoneX;
	float deadzoneY;

public:
	Gamepad() : deadzoneX(0.05f), deadzoneY(0.02f) {}
	Gamepad(float dzX, float dzY) : deadzoneX(dzX), deadzoneY(dzY) {}

	float leftStickX;
	float leftStickY;
	float rightStickX;
	float rightStickY;
	float leftTrigger;
	float rightTrigger;

	int  GetPort();
	XINPUT_GAMEPAD* GetState();
	bool CheckConnection();
	bool Refresh();
	bool IsPressed(WORD);
};

int Gamepad::GetPort()
{
	return cId + 1;
}

XINPUT_GAMEPAD* Gamepad::GetState()
{
	return &state.Gamepad;
}

bool Gamepad::CheckConnection()
{
	int controllerId = -1;

	for (DWORD i = 0; i < XUSER_MAX_COUNT && controllerId == -1; i++)
	{
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));

		if (XInputGetState(i, &state) == ERROR_SUCCESS)
			controllerId = i;
	}

	cId = controllerId;

	return controllerId != -1;
}

// Returns false if the controller has been disconnected
bool Gamepad::Refresh()
{
	if (cId == -1)
		CheckConnection();

	if (cId != -1)
	{
		ZeroMemory(&state, sizeof(XINPUT_STATE));
		if (XInputGetState(cId, &state) != ERROR_SUCCESS)
		{
			cId = -1;
			return false;
		}

		float normLX = fmaxf(-1, (float)state.Gamepad.sThumbLX / 32767);
		float normLY = fmaxf(-1, (float)state.Gamepad.sThumbLY / 32767);

		leftStickX = (abs(normLX) < deadzoneX ? 0 : (abs(normLX) - deadzoneX) * (normLX / abs(normLX)));
		leftStickY = (abs(normLY) < deadzoneY ? 0 : (abs(normLY) - deadzoneY) * (normLY / abs(normLY)));

		if (deadzoneX > 0) leftStickX *= 1 / (1 - deadzoneX);
		if (deadzoneY > 0) leftStickY *= 1 / (1 - deadzoneY);

		float normRX = fmaxf(-1, (float)state.Gamepad.sThumbRX / 32767);
		float normRY = fmaxf(-1, (float)state.Gamepad.sThumbRY / 32767);

		rightStickX = (abs(normRX) < deadzoneX ? 0 : (abs(normRX) - deadzoneX) * (normRX / abs(normRX)));
		rightStickY = (abs(normRY) < deadzoneY ? 0 : (abs(normRY) - deadzoneY) * (normRY / abs(normRY)));

		if (deadzoneX > 0) rightStickX *= 1 / (1 - deadzoneX);
		if (deadzoneY > 0) rightStickY *= 1 / (1 - deadzoneY);

		leftTrigger = (float)state.Gamepad.bLeftTrigger / 255;
		rightTrigger = (float)state.Gamepad.bRightTrigger / 255;

		return true;
	}
	return false;
}

bool Gamepad::IsPressed(WORD button)
{
	return (state.Gamepad.wButtons & button) != 0;
}

//This function loops a bit faster than every frame.
void controls::Loop()
{
	int temp = 0;
	while (temp != 1)
	{
		Gamepad gamepad;

		bool wasConnected = true;

		while (true)
		{
			Sleep(100);

			if (!gamepad.Refresh())
			{
				if (wasConnected)
				{
					wasConnected = false;

					cout << "Please connect an Xbox 360 controller." << endl;
				}
			}
			else
			{
				if (!wasConnected)
				{
					wasConnected = true;

					cout << "Controller connected on port " << gamepad.GetPort() << endl;
				}

				cout << "Left thumb stick: (" << gamepad.leftStickX << ", " << gamepad.leftStickY << ")   Right thumb stick : (" << gamepad.rightStickX << ", " << gamepad.rightStickY << ")" << endl;

				cout << "Left analog trigger: " << gamepad.leftTrigger << "   Right analog trigger: " << gamepad.rightTrigger << endl;
				
				uintptr_t baseAddr = Internal::Memory::getModule("NSUNS4.exe");
				uintptr_t button1Addr = Internal::Memory::getAddress(baseAddr + 0x01616300, { 0x8B0 });
				uintptr_t button2Addr = Internal::Memory::getAddress(baseAddr + 0x016BDA78, { 0x340 });
				int button1 = Internal::Memory::read<uint8_t>(1 + button1Addr);
				int button2 = Internal::Memory::read<uint8_t>(1 + button2Addr);
				cout << "Button 1 Addr: " << + button1Addr << endl;
				cout << "Button 2 Addr: " << button2Addr << endl;
				cout << "Button 1: " << button1 << endl;
				cout << "Button 2: " << button2 << endl;

				if (gamepad.IsPressed(XINPUT_GAMEPAD_A))
				{
					if (APress == 0)
					{
						Internal::Memory::write<uint8_t>(1 + button1Addr, 64);
						Internal::Memory::write<uint8_t>(1 + button2Addr, 64);
						cout << "(A) button pressed" << endl;
						APress = 1;
					}
					else
					{
						cout << "(A) button held" << endl;
						AHold = 1;
						APress == 0;
					}
					button1 = Internal::Memory::read<uint8_t>(1 + button1Addr);
					button2 = Internal::Memory::read<uint8_t>(1 + button2Addr);
				}
				else
				{
					button1 = Internal::Memory::read<uint8_t>(1 + button1Addr);
					button2 = Internal::Memory::read<uint8_t>(1 + button2Addr);
					if (AHold == 1)
					{
						Internal::Memory::write<uint8_t>(1 + button1Addr, button1 - 64);
						Internal::Memory::write<uint8_t>(1 + button2Addr, button2 - 64);
						cout << "(A) button released" << endl;
						APress = 0;
						AHold = 0;
					}
				}
			}
		}
	}
}