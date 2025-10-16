#pragma once
#include "../FCore.h"

class CThing;

class CTCEnemy {
public:
	void RemoveEnemyThing(CThing* creature);
	void SetFaction(CCharString* faction);
	void AddAlly(CThing* creature);
	bool IsEnemyOf(CThing* creature);
};