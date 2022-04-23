#pragma once
#include "World.h"
#include "PlayerManager.h"

class CMainGameComponent {
public:
	static CMainGameComponent* Get();

	CWorld* GetWorld();
	CPlayerManager* GetPlayerManager();
};


