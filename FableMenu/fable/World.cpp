#include "World.h"
#include "..\core.h"

int& CWorld::ms_curFrame = *(int*)0x13B89BC;

void CWorld::SetMinimap(bool status)
{
	*(bool*)(this + 0xDD) = status;
}

CPlayer* CWorld::GetPlayer(int id)
{
	return CallMethodAndReturn<CPlayer*, 0x4498C0, CWorld*, int>(this, id);
}

CBulletTimeManager* CWorld::GetBulletTime()
{
	return *(CBulletTimeManager**)((int)this + 104);
}

CScriptInfoManager* CWorld::GetScriptInfoManager()
{
	return *(CScriptInfoManager**)((int)this + 88);
}

CGameScriptInterface* CWorld::GetGameScriptInterface()
{
	return *(CGameScriptInterface**)((int)this + 56);
}
