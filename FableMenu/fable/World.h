#pragma once
#include "Player.h"
#include "BulletTime.h"
#include "Script.h"
#include "ScriptInterface.h"
#include "ThingSearchTools.h"

class CWorld {
public:
	bool isLoadRegion();
	bool isLoadSave();
	bool* GetMinimap();
	void SetMinimap(bool status);
	void TeleportHeroToHSP(CCharString* hsp_name);
	void AutoSave(int ignore_being_between_start_and_finish_screens);

	CPlayer* GetPlayer(int id);
	CBulletTimeManager* GetBulletTime();
	CThingSearchTools* GetThingSearchTools();
	CScriptInfoManager* GetScriptInfoManager();
	CGameScriptInterface* GetGameScriptInterface();

	static int& ms_curFrame;
};