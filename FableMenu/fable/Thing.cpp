#include "Thing.h"
#include "Hero.h"
#include "..\core.h"


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

CTCHero* CThing::GetHero()
{
    int v29 = 41;
    int v5 = CallMethodAndReturn<int, 0x40F020, int, int*>((int)((int)this + 68), &v29);
    if (v5 == *(int*)(this + 72) || *(int*)v5 > 41)
        v5 = *(int*)(this + 72);
    return *(CTCHero**)(v5 + 4);
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
