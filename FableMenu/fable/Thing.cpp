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

CTCLight* CThing::GetLight()
{
    int v29 = 39;
    int v5 = CallMethodAndReturn<int, 0x40F020, int, int*>((int)((int)this + 68), &v29);
    if (v5 == *(int*)(this + 72) || *(int*)v5 > 39)
        v5 = *(int*)(this + 72);
    return *(CTCLight**)(v5 + 4);
}

CTCInventoryAbilities* CThing::GetInventoryAbilities()
{
    int v29 = 111;
    int v5 = CallMethodAndReturn<int, 0x40F020, int, int*>((int)((int)this + 68), &v29);
    if (v5 == *(int*)(this + 72) || *(int*)v5 > 111)
        v5 = *(int*)(this + 72);
    return *(CTCInventoryAbilities**)(v5 + 4);
}

CTCWeapon* CThing::GetWeapon()
{
    int v29 = 72;
    int v5 = CallMethodAndReturn<int, 0x40F020, int, int*>((int)((int)this + 68), &v29);
    if (v5 == *(int*)(this + 72) || *(int*)v5 > 72)
        v5 = *(int*)(this + 72);
    return *(CTCWeapon**)(v5 + 4);
}

CTCObjectAugmentations* CThing::GetObjectAugmentations()
{
    int v29 = 191;
    int v5 = CallMethodAndReturn<int, 0x40F020, int, int*>((int)((int)this + 68), &v29);
    if (v5 == *(int*)(this + 72) || *(int*)v5 > 191)
        v5 = *(int*)(this + 72);
    return *(CTCObjectAugmentations**)(v5 + 4);
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

bool CThing::SetCurrentAction(CTCBase* action)
{
    return CallMethodAndReturn<bool, 0x6644F0, CThing*, CTCBase*>(this, action);
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

void CThing::RemoveTC(ETCInterfaceType type)
{
    CallMethod<0x4C9840, CThing*, ETCInterfaceType>(this, type);
}

bool CThing::HasTC(int interface_type)
{
    return CallMethodAndReturn<bool, 0x4118C0, CThing*, int>(this, interface_type);
}

CTCDParticleEmitter* CThing::GetParticleEmitter()
{
    int v29 = 75;
    int v5 = CallMethodAndReturn<int, 0x40F020, int, int*>((int)((int)this + 68), &v29);
    if (v5 == *(int*)(this + 72) || *(int*)v5 > 75)
        v5 = *(int*)(this + 72);
    return *(CTCDParticleEmitter**)(v5 + 4);
}

CTCPhysicsStandard* CThing::GetPhysicsStandard()
{
    int v29 = 2;
    int v5 = CallMethodAndReturn<int, 0x40F020, int, int*>((int)((int)this + 68), &v29);
    if (v5 == *(int*)(this + 72) || *(int*)v5 > 2)
        v5 = *(int*)(this + 72);
    return *(CTCPhysicsStandard**)(v5 + 4);
}

CTCFollowed* CThing::GetFollowed()
{
    int v29 = 188;
    int v5 = CallMethodAndReturn<int, 0x40F020, int, int*>((int)((int)this + 68), &v29);
    if (v5 == *(int*)(this + 72) || *(int*)v5 > 188)
        v5 = *(int*)(this + 72);
    return *(CTCFollowed**)(v5 + 4);
}

CreatureAI* CThing::GetCreatureAI()
{
    int v29 = 11;
    int v5 = CallMethodAndReturn<int, 0x40F020, int, int*>((int)((int)this + 68), &v29);
    if (v5 == *(int*)(this + 72) || *(int*)v5 > 11)
        v5 = *(int*)(this + 72);
    return *(CreatureAI**)(v5 + 4);
}

CTCAIScratchPad* CThing::GetAIScratchPad()
{
    int v29 = 170;
    int v5 = CallMethodAndReturn<int, 0x40F020, int, int*>((int)((int)this + 68), &v29);
    if (v5 == *(int*)(this + 72) || *(int*)v5 > 170)
        v5 = *(int*)(this + 72);
    return *(CTCAIScratchPad**)(v5 + 4);
}

CTCHeroOpinionLog* CThing::GetHeroOpinionLog()
{
    int v29 = 79;
    int v5 = CallMethodAndReturn<int, 0x40F020, int, int*>((int)((int)this + 68), &v29);
    if (v5 == *(int*)(this + 72) || *(int*)v5 > 79)
        v5 = *(int*)(this + 72);
    return *(CTCHeroOpinionLog**)(v5 + 4);
}

CTCWife* CThing::GetWife()
{
    int v29 = 215;
    int v5 = CallMethodAndReturn<int, 0x40F020, int, int*>((int)((int)this + 68), &v29);
    if (v5 == *(int*)(this + 72) || *(int*)v5 > 215)
        v5 = *(int*)(this + 72);
    return *(CTCWife**)(v5 + 4);
}

CTCHeroMorph* CThing::GetHeroMorph()
{
    int v29 = 3;
    int v5 = CallMethodAndReturn<int, 0x40F020, int, int*>((int)((int)this + 68), &v29);
    if (v5 == *(int*)(this + 72) || *(int*)v5 > 3)
        v5 = *(int*)(this + 72);
    return *(CTCHeroMorph**)(v5 + 4);
}

CTCCombat* CThing::GetCombat()
{
    int v29 = 48;
    int v5 = CallMethodAndReturn<int, 0x40F020, int, int*>((int)((int)this + 68), &v29);
    if (v5 == *(int*)(this + 72) || *(int*)v5 > 48)
        v5 = *(int*)(this + 72);
    return *(CTCCombat**)(v5 + 4);
}

CTCCreatureModeManager* CThing::GetCreatureModeManager()
{
    int v29 = 49;
    int v5 = CallMethodAndReturn<int, 0x40F020, int, int*>((int)((int)this + 68), &v29);
    if (v5 == *(int*)(this + 72) || *(int*)v5 > 49)
        v5 = *(int*)(this + 72);
    return *(CTCCreatureModeManager**)(v5 + 4);
}

CTCScriptedControl* CThing::GetScriptedControl()
{
    int v29 = 31;
    int v5 = CallMethodAndReturn<int, 0x40F020, int, int*>((int)((int)this + 68), &v29);
    if (v5 == *(int*)(this + 72) || *(int*)v5 > 31)
        v5 = *(int*)(this + 72);
    return *(CTCScriptedControl**)(v5 + 4);
}

CTCActionUse* CThing::GetActionUse()
{
    int v29 = 13;
    int v5 = CallMethodAndReturn<int, 0x40F020, int, int*>((int)((int)this + 68), &v29);
    if (v5 == *(int*)(this + 72) || *(int*)v5 > 13)
        v5 = *(int*)(this + 72);
    return *(CTCActionUse**)(v5 + 4);
}

CTCVillage* CThing::GetVillage()
{
    int v29 = 34;
    int v5 = CallMethodAndReturn<int, 0x40F020, int, int*>((int)((int)this + 68), &v29);
    if (v5 == *(int*)(this + 72) || *(int*)v5 > 34)
        v5 = *(int*)(this + 72);
    return *(CTCVillage**)(v5 + 4);
}

CTCVillageMember* CThing::GetVillageMember()
{
    int v29 = 35;
    int v5 = CallMethodAndReturn<int, 0x40F020, int, int*>((int)((int)this + 68), &v29);
    if (v5 == *(int*)(this + 72) || *(int*)v5 > 35)
        v5 = *(int*)(this + 72);
    return *(CTCVillageMember**)(v5 + 4);
}

CTCInventoryClothing* CThing::GetInventoryClothing()
{
    int v29 = 18;
    int v5 = CallMethodAndReturn<int, 0x40F020, int, int*>((int)((int)this + 68), &v29);
    if (v5 == *(int*)(this + 72) || *(int*)v5 > 18)
        v5 = *(int*)(this + 72);
    return *(CTCInventoryClothing**)(v5 + 4);
}

CTCCarrying* CThing::GetCarrying()
{
    int v29 = 70;
    int v5 = CallMethodAndReturn<int, 0x40F020, int, int*>((int)((int)this + 68), &v29);
    if (v5 == *(int*)(this + 72) || *(int*)v5 > 70)
        v5 = *(int*)(this + 72);
    return *(CTCCarrying**)(v5 + 4);
}

CTCInventoryItem* CThing::GetInventoryItem()
{
    int v29 = 26;
    int v5 = CallMethodAndReturn<int, 0x40F020, int, int*>((int)((int)this + 68), &v29);
    if (v5 == *(int*)(this + 72) || *(int*)v5 > 26)
        v5 = *(int*)(this + 72);
    return *(CTCInventoryItem**)(v5 + 4);
}

CTCThingOwner* CThing::GetThingOwner()
{
    int v29 = 33;
    int v5 = CallMethodAndReturn<int, 0x40F020, int, int*>((int)((int)this + 68), &v29);
    if (v5 == *(int*)(this + 72) || *(int*)v5 > 33)
        v5 = *(int*)(this + 72);
    return *(CTCThingOwner**)(v5 + 4);
}

CTCOwnedEntity* CThing::GetOwnedEntity()
{
    int v29 = 51;
    int v5 = CallMethodAndReturn<int, 0x40F020, int, int*>((int)((int)this + 68), &v29);
    if (v5 == *(int*)(this + 72) || *(int*)v5 > 51)
        v5 = *(int*)(this + 72);
    return *(CTCOwnedEntity**)(v5 + 4);
}

CTCBuyableHouse* CThing::GetBuyableHouse()
{
    int v29 = 213;
    int v5 = CallMethodAndReturn<int, 0x40F020, int, int*>((int)((int)this + 68), &v29);
    if (v5 == *(int*)(this + 72) || *(int*)v5 > 213)
        v5 = *(int*)(this + 72);
    return *(CTCBuyableHouse**)(v5 + 4);
}

CTCHaste* CThing::GetHaste()
{
    int v29 = 140;
    int v5 = CallMethodAndReturn<int, 0x40F020, int, int*>((int)((int)this + 68), &v29);
    if (v5 == *(int*)(this + 72) || *(int*)v5 > 140)
        v5 = *(int*)(this + 72);
    return *(CTCHaste**)(v5 + 4);
}

CTCDoor* CThing::GetDoor()
{
    int v29 = 38;
    int v5 = CallMethodAndReturn<int, 0x40F020, int, int*>((int)((int)this + 68), &v29);
    if (v5 == *(int*)(this + 72) || *(int*)v5 > 38)
        v5 = *(int*)(this + 72);
    return *(CTCDoor**)(v5 + 4);
}

CTCQuestCard* CThing::GetQuestCard()
{
    int v29 = 108;
    int v5 = CallMethodAndReturn<int, 0x40F020, int, int*>((int)((int)this + 68), &v29);
    if (v5 == *(int*)(this + 72) || *(int*)v5 > 108)
        v5 = *(int*)(this + 72);
    return *(CTCQuestCard**)(v5 + 4);
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