#pragma once
#include "FCore.h"

class CThing;

class CQuestManager
{
public:
	static CQuestManager* Get();

	bool ActivateQuest(CCharString* name, bool game, bool load_resources);
	bool IsQuestActive(CCharString* name);
	bool IsQuestCardActive(CCharString* name);
	bool IsAnyQuestActive();
	void DeactivateQuest(CCharString* active_quest, int flags);
	
	bool SetQuestAsCompleted(CCharString* script_name, int display_screen, bool auto_save, int force_regular_auto_save);
	CThing* GetActiveQuestCardFromScriptName(CCharString* script_name);
	int GetIndexFromRegisteredQuest(CCharString* name);

	void DeactivateAllQuests();
};