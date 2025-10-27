#include "UserProfileManager.h"
#include "../core.h"

CUserProfileManager* CUserProfileManager::Get()
{
	return CallAndReturn<CUserProfileManager*, 0x40D2A0>();
}

void CUserProfileManager::SetAssignedInputKeyboard(EGameAction action, EInputKey key, bool passive)
{
	CallMethod<0x407A70, CUserProfileManager*, EGameAction, EInputKey, bool>(this, action, key, passive);
}

void CUserProfileManager::GetAssignedInputForAction(EGameAction action, bool passive, CActionInputControl* input_control)
{
	CallMethod<0x408C90, CUserProfileManager*, EGameAction, bool, CActionInputControl*>(this, action, passive, input_control);
}