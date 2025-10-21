#include "World.h"
#include "..\core.h"

int& CWorld::ms_curFrame = *(int*)0x13B89BC;

void CWorld::SetMinimap(bool status)
{
	*(bool*)(this + 221) = status;
}

bool* CWorld::GetMinimap()
{
	return (bool*)(this + 221);
}

bool CWorld::isLoadRegion()
{
	return *(bool*)((char*)this + 0x104);
}

bool CWorld::isLoadSave()
{
	return *(bool*)((char*)this + 0xF8);
}

CPlayer* CWorld::GetPlayer(int id)
{
	return CallMethodAndReturn<CPlayer*, 0x4498C0, CWorld*, int>(this, id);
}

CBulletTimeManager* CWorld::GetBulletTime()
{
	return *(CBulletTimeManager**)((int)this + 104);
}

CThingSearchTools* CWorld::GetThingSearchTools()
{
	return *(CThingSearchTools**)(this + 32);
}

CScriptInfoManager* CWorld::GetScriptInfoManager()
{
	return *(CScriptInfoManager**)((int)this + 88);
}

CGameScriptInterface* CWorld::GetGameScriptInterface()
{
	return *(CGameScriptInterface**)((int)this + 56);
}

void CWorld::TeleportHeroToHSP(CCharString* hsp_name)
{
	CallMethod<0x4A0940, CWorld*, CCharString*>(this, hsp_name);
}

void CWorld::AutoSave(int ignore_being_between_start_and_finish_screens)
{
	CallMethod<0x4A0AE0, CWorld*, int>(this, ignore_being_between_start_and_finish_screens);
}