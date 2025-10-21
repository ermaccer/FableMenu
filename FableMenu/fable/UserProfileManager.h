#pragma once
#include "GameInputProcess.h"

class CUserProfileManager
{
public:
	static CUserProfileManager* Get();
	void SetAssignedInputKeyboard(EGameAction action, EInputKey key, bool passive);
    void GetAssignedInputForAction(EGameAction action, bool passive, CActionInputControl* input_control);
};