#include "QuestManager.h"
#include "../core.h"

CQuestManager* CQuestManager::Get()
{
	return *(CQuestManager**)(0x13B89FC);
}

bool CQuestManager::ActivateQuest(CCharString* name, bool game, bool load_resources)
{
	return CallMethodAndReturn<bool, 0x4B4A10, CQuestManager*, CCharString*, bool, bool>(this, name, game, load_resources);
}

bool CQuestManager::IsQuestActive(CCharString* name)
{
	return CallMethodAndReturn<bool, 0x4AF610, CQuestManager*, CCharString*>(this, name);
}

bool CQuestManager::IsQuestCardActive(CCharString* name)
{
	return CallMethodAndReturn<bool, 0x4AF560, CQuestManager*, CCharString*>(this, name);
}

bool CQuestManager::SetQuestAsCompleted(CCharString* script_name, int display_screen, bool auto_save, int force_regular_auto_save)
{
	return CallMethodAndReturn<bool, 0x4B1D30, CQuestManager*, CCharString*, int, bool, int>(this, script_name, display_screen, auto_save, force_regular_auto_save);
}

bool CQuestManager::IsAnyQuestActive()
{
	return CallMethodAndReturn<bool, 0x4B1080, CQuestManager*>(this);
}

void CQuestManager::DeactivateQuest(CCharString* active_quest, int flags)
{
	CallMethod<0x4B43D0, CQuestManager*, CCharString*, int>(this, active_quest, flags);
}

void CQuestManager::DeactivateAllQuests()
{
	CallMethod<0x4B4450, CQuestManager*>(this);
}

CThing* CQuestManager::GetActiveQuestCardFromScriptName(CCharString* script_name)
{
	return CallMethodAndReturn<CThing*, 0x4B0C80, CQuestManager*, CCharString*>(this, script_name);
}

int CQuestManager::GetIndexFromRegisteredQuest(CCharString* name)
{
	return CallMethodAndReturn<int, 0x4AF740, CQuestManager*, CCharString*>(this, name);
}