#pragma once
#include "Player.h"
#include "BulletTime.h"
#include "Script.h"

class CWorld {
public:
	char pad[221];
	bool m_bMinimap;
	void SetMinimap(bool status);
	CPlayer* GetPlayer(int id);
	CBulletTimeManager* GetBulletTime();
	CScriptInfoManager* GetScriptInfoManager();

	static int& ms_curFrame;
};