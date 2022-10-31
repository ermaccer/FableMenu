#pragma once
#include "FCore.h"

class CQuestManager {
public:
	bool ActivateQuest(CCharString* name, bool game, bool load_resources);
	bool IsActive(CCharString* name);
	void DeactivateQuest(CCharString* name, int flags);

	static CQuestManager* Get();
};

