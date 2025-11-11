#include "eKeyboardMan.h"
#include <iostream>
#include <Windows.h>

eVKKeyCode eKeyboardMan::GetLastKey()
{
	eVKKeyCode key = VK_KEY_NULL;
	for (int i = 0; i < VK_KEY_MAX; i++)
	{
		if (GetKeyState(i) & 0x8000)
		{
			key = (eVKKeyCode)i;
			break;
		}
	}
	return key;
}

const char* eKeyboardMan::KeyToString(int code)
{
	static wchar_t buff[128] = {};
	static char utf8Buff[256] = {};
	UINT key = MapVirtualKey(code, MAPVK_VK_TO_VSC);

	int result = GetKeyNameTextW((key << 16), buff, sizeof(buff));

	if (code == VK_UP)
		return "Up";
	else if (code == VK_DOWN)
		return "Down";
	else if (code == VK_LEFT)
		return "Left";
	else if (code == VK_RIGHT)
		return "Right";
	else if (result)
	{
		int size = WideCharToMultiByte(CP_UTF8, 0, buff, result, NULL, 0, NULL, NULL);

		WideCharToMultiByte(CP_UTF8, 0, buff, result, utf8Buff, size, NULL, NULL);

		utf8Buff[size] = '\0';
		return utf8Buff;
	}
	else
		return "Unknown";
}

EInputKey eKeyboardMan::GetInputFromVKKeyCode(int code)
{
	for (int i = 0; i < VK_KEY_MAX; i++)
	{
		if (gameKeyCodes[i] == code)
		{
			return (EInputKey)i;
		}
	}

	return KB_NULL;
}