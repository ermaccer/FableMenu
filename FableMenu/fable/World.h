#pragma once
#include "Player.h"
#include "BulletTime.h"
#include "Script.h"
#include "ScriptInterface.h"
#include "ThingSearchTools.h"

class CWorld {
public:
	bool* GetMinimap();
	void SetMinimap(bool status);
	CPlayer* GetPlayer(int id);

	CBulletTimeManager* GetBulletTime();
	CThingSearchTools* GetThingSearchTools();
	CScriptInfoManager* GetScriptInfoManager();
	CGameScriptInterface* GetGameScriptInterface();

	static int& ms_curFrame;
};