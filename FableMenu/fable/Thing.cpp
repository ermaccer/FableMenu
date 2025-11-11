#include "Thing.h"
#include "..\core.h"

CThingManager* CThing::GetCurrentThingManager()
{
    return *(CThingManager**)0x13B8A1C;
}

const CPlayer* CThing::PeekPlayer()
{
    return CallMethodAndReturn<const CPlayer*, 0x4C7A10, CThing*>(this);
}

CTCBase* CThing::GetTC(ETCInterfaceType id)
{
    if (!HasTC(id)) return nullptr;

    int v29 = id;
    int v5 = CallMethodAndReturn<int, 0x40F020, int, int*>((int)((int)this + 68), &v29);
    if (v5 == *(int*)(this + 72) || *(int*)v5 > id)
        v5 = *(int*)(this + 72);
    return *(CTCBase**)(v5 + 4);
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

ECreatureType CThing::GetCreatureType()
{
    return CallMethodAndReturn<ECreatureType, 0x662000, CThing*>(this);
}

ECreatureProperty CThing::GetCreatureProperty()
{
    return CallMethodAndReturn<ECreatureProperty, 0x662010, CThing*>(this);
}

int CThing::GetActionID()
{
    return CallMethodAndReturn<int, 0x692620, CThing*>(this);
}

void CThing::LockAllDoors(bool lock, bool avoid_hero)
{
    CallMethod<0x82DB00, CThing*, bool, bool>(this, lock, avoid_hero);
}

void CThing::Kill(bool perform)
{
    CallMethod<0x4C9B80, CThing*, bool>(this, perform);
}

bool CThing::isThingAlive()
{
    return CallMethodAndReturn<bool, 0x4CC340, CThing*>(this);
}

void CThing::SetInLimbo(bool on)
{
    CallMethod<0x4C8CF0, CThing*, int>(this, on);
}

bool CThing::SetCurrentAction(CTCBase* action)
{
    return CallMethodAndReturn<bool, 0x6644F0, CThing*, CTCBase*>(this, action);
}

bool CThing::IsFreeToPerformAction(CTCBase* action)
{
    return CallMethodAndReturn<bool, 0x662210, CThing*,CTCBase*>(this, action);
}

bool CThing::HasPrecedingAction()
{
    return CallMethodAndReturn<bool, 0x692EC0, CThing*>(this);
}

bool CThing::IsChild()
{
    return CallMethodAndReturn<bool, 0x661F70, CThing*>(this);
}

void CThing::SetNewBrain(int brain_def)
{
    CallMethod<0x833010, CThing*, int>(this, brain_def);
}

void CThing::LearnAbility(EHeroAbility ability, bool learn, int quick_access_slot, bool silent)
{
    CallMethod<0x6AC690, CThing*, EHeroAbility, int, int, int>(this, ability, learn, quick_access_slot, silent);
}

void CThing::LearnExpression(CCharString* expression_name, int quick_access_slot, bool silent)
{
    CallMethod<0x6AC430, CThing*, CCharString*, int, bool>(this, expression_name, quick_access_slot, silent);
}

CWorldMap* CThing::GetWorldMap()
{
    return CallAndReturn<CWorldMap*, 0x4C79D0>();
}

CThingSearchTools* CThing::GetThingSearchTools()
{
    return CallMethodAndReturn<CThingSearchTools*, 0x686D80, CThing*>(this);
}

CDefString* CThing::GetDefName()
{
    CDefString def;
    return CallMethodAndReturn<CDefString*, 0x4C7CC0, CThing*, CDefString*>(this, &def);
}

CTCBase* CThing::AddTC(CCharString* name, int voverride, int pparams_base)
{
    return CallMethodAndReturn<CTCBase*, 0x4C9D60, CThing*, CCharString*, int, int>(this, name, voverride, pparams_base);
}

void CThing::RemoveTC(ETCInterfaceType id)
{
    CallMethod<0x4C9840, CThing*, ETCInterfaceType>(this, id);
}

bool CThing::HasTC(ETCInterfaceType id)
{
    return CallMethodAndReturn<bool, 0x4118C0, CThing*, ETCInterfaceType>(this, id);
}

void CThing::ClearQueuedActions()
{
    CallMethod<0x663600, CThing*>(this);
}

void CThing::FinishCurrentAction()
{
    CallMethod<0x662650, CThing*>(this);
}

int CThing::GetThingID(char* name)
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

void CTCLook::GetHeadLocation(CVector* out)
{
    CallMethod<0x751B30, CTCLook*, CVector*>(this, out);
}