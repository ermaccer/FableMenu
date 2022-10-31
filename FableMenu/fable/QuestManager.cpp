#include "QuestManager.h"
#include "..\core.h"

bool CQuestManager::ActivateQuest(CCharString* name, bool game, bool load_resources)
{
    return CallMethodAndReturn<bool, 0x4B4A10, CQuestManager*, CCharString*, bool, bool>(this, name, game, load_resources);
}

bool CQuestManager::IsActive(CCharString* name)
{
    return CallMethodAndReturn<bool, 0x4AF610, CQuestManager*, CCharString*>(this, name);
}

void CQuestManager::DeactivateQuest(CCharString* name, int flags)
{
    CallMethod<0x4B43D0, CQuestManager*, CCharString*, int>(this, name, flags);
}

CQuestManager* CQuestManager::Get()
{
    return *(CQuestManager**)(0x13B89FC);
}
