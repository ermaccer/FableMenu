#include "ModeManager.h"
#include "../../core.h"

CTCBase* CTCCreatureModeManager::GetCurrentCreatureMode()
{
    return CallMethodAndReturn<CTCBase*, 0x73A6E0, CTCCreatureModeManager*>(this);
}

bool CTCCreatureModeManager::AddMode(NCreatureMode mode)
{
    return CallMethodAndReturn<bool, 0x73AE10, CTCCreatureModeManager*,int>(this,mode);
}

void CTCCreatureModeManager::SetupDefaultMode()
{
    return CallMethod<0x73AF60, CTCCreatureModeManager*>(this);
}

void CTCCreatureModeManager::RemoveAllModes()
{
    return CallMethod<0xB443B0, CTCCreatureModeManager*>(this);
}

void CTCCreatureModeManager::RemoveMode(NCreatureMode mode)
{
    CallMethod<0x73ABA0, CTCCreatureModeManager*, int>(this, mode);
}

void CTCCreatureModeManager::ResetModes()
{
    return CallMethod<0x8D68A0, CTCCreatureModeManager*>(this);
}

bool CTCCreatureModeManager::isModeActive(NCreatureMode mode)
{
    return CallMethodAndReturn<bool, 0x73A8A0, CTCCreatureModeManager*,int>(this, mode);
}