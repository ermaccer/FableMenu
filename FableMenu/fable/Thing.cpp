#include "Thing.h"
#include "Hero.h"
#include "..\core.h"


CTCBase* CThing::GetTC(int id)
{
    int v29 = id;
    int v5 = CallMethodAndReturn<int, 0x40F020, int, int*>((int)((int)this + 68), &v29);
    if (v5 == *(int*)(this + 72) || *(int*)v5 > id)
        v5 = *(int*)(this + 72);
    return *(CTCBase**)(v5 + 4);
}

CTCHeroStats* CThing::GetHeroStats()
{
    int v29 = 4;
    int v5 = CallMethodAndReturn<int, 0x40F020, int, int*>((int)((int)this + 68), &v29);
    if (v5 == *(int*)(this + 72) || *(int*)v5 > 4)
        v5 = *(int*)(this + 72);
    return *(CTCHeroStats**)(v5 + 4);
}

CTCHeroMorph* CThing::GetHeroMorph()
{
    int v29 = 3;
    int v5 = CallMethodAndReturn<int, 0x40F020, int, int*>((int)((int)this + 68), &v29);
    if (v5 == *(int*)(this + 72) || *(int*)v5 > 3)
        v5 = *(int*)(this + 72);
    return *(CTCHeroMorph**)(v5 + 4);
}

CTCHeroExperience* CThing::GetHeroExperience()
{
    int v29 = 104;
    int v5 = CallMethodAndReturn<int, 0x40F020, int, int*>((int)((int)this + 68), &v29);
    if (v5 == *(int*)(this + 72) || *(int*)v5 > 104)
        v5 = *(int*)(this + 72);
    return *(CTCHeroExperience**)(v5 + 4);
}

CTCHero* CThing::GetHero()
{
    int v29 = 41;
    int v5 = CallMethodAndReturn<int, 0x40F020, int, int*>((int)((int)this + 68), &v29);
    if (v5 == *(int*)(this + 72) || *(int*)v5 > 41)
        v5 = *(int*)(this + 72);
    return *(CTCHero**)(v5 + 4);
}

CTCEnemy* CThing::GetEnemy()
{
    int v29 = 73;
    int v5 = CallMethodAndReturn<int, 0x40F020, int, int*>((int)((int)this + 68), &v29);
    if (v5 == *(int*)(this + 72) || *(int*)v5 > 73)
        v5 = *(int*)(this + 72);
    return *(CTCEnemy**)(v5 + 4);
}

CTCRegionFollower* CThing::GetRegionFollower()
{
    int v29 = 122;
    int v5 = CallMethodAndReturn<int, 0x40F020, int, int*>((int)((int)this + 68), &v29);
    if (v5 == *(int*)(this + 72) || *(int*)v5 > 122)
        v5 = *(int*)(this + 72);
    return *(CTCRegionFollower**)(v5 + 4);
}

CTCLook* CThing::GetLook()
{
    int v29 = 67;
    int v5 = CallMethodAndReturn<int, 0x40F020, int, int*>((int)((int)this + 68), &v29);
    if (v5 == *(int*)(this + 72) || *(int*)v5 > 67)
        v5 = *(int*)(this + 72);
    return *(CTCLook**)(v5 + 4);
}

CTCGraphicAppearance* CThing::GetGraphicAppearance()
{
    int v29 = 91;
    int v5 = CallMethodAndReturn<int, 0x40F020, int, int*>((int)((int)this + 68), &v29);
    if (v5 == *(int*)(this + 72) || *(int*)v5 > 91)
        v5 = *(int*)(this + 72);
    return *(CTCGraphicAppearance**)(v5 + 4);
}

CTCScriptedControl* CThing::GetSC()
{
    int v29 = 31;
    int v5 = CallMethodAndReturn<int, 0x40F020, int, int*>((int)((int)this + 68), &v29);
    if (v5 == *(int*)(this + 72) || *(int*)v5 > 31)
        v5 = *(int*)(this + 72);
    return *(CTCScriptedControl**)(v5 + 4);
}

CTCPhysics* CThing::GetPhysics()
{
    return (CTCPhysics*)GetTC(2);
}

CVector* CThing::GetPosition()
{
    return CallMethodAndReturn<CVector*, 0x4C73D0, CThing*>(this);
}

CThing* __fastcall CreateThing(int id, CVector* pos, int plr, int unk, int unk2, char* name)
{
    CCharString tmp(name);
    return FASTCallAndReturn<CThing*, 0x703210, int, CVector*, int, int, int, CCharString*>(id, pos, plr, unk, unk2, &tmp);
}

int GetThingID(char* name)
{
    int id = -1;
    int manager = CallAndReturn<int, 0x44C6B0>();
    if (manager)
    {
        CCharString str(name);
        id = CallMethodAndReturn<int, 0x9AD410, int, CCharString*>(manager, &str);
    }
    return id;
}

CThing* __fastcall CreateCreature(int id, CVector* pos, int plr)
{
    CreatureAI ai = {};
    ai.IsPlayer = false;
    ai.Draw = true;
    ai.unk[0] = true;

    return FASTCallAndReturn<CThing*, 0x833800, int, CVector*, int, CreatureAI*>(id, pos, plr, &ai);
}



void CTCEnemy::SetFaction(CCharString* str)
{
    CallMethod<0x76C810, CTCEnemy*, CCharString*>(this, str);
}

void CTCEnemy::AddAlly(CThing* thing)
{
    CallMethod<0x76D270, CTCEnemy*, CThing*>(this, thing);
}

void CTCRegionFollower::AddFollower(CThing* thing)
{
    CallMethod<0x6AEDC0, CTCRegionFollower*, CThing*>(this, thing);
}

void CTCLook::GetHeadLocation(CVector* out)
{
    CallMethod<0x751B30, CTCLook*, CVector*>(this, out);
}

void CTCGraphicAppearance::SetAlpha(char value)
{
    CallMethod<0x4BFAC0, CTCGraphicAppearance*,char>(this, value);
}

void CTCGraphicAppearance::SetColor(int* color, CTCBase* base)
{
    CallMethod<0x4C00B0, CTCGraphicAppearance*, int*, CTCBase*>(this, color, base);
}

void CTCGraphicAppearance::SetScale(float value)
{
    CallMethod<0x4BFA50, CTCGraphicAppearance*, float>(this, value);
}

void CTCScriptedControl::AddAction(CActionBase* action)
{
    CallMethod<0x7137D0, CTCScriptedControl*, CActionBase*>(this, action);
}
