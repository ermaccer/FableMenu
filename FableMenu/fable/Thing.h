#pragma once
#include "FCore.h"

#include "ThingComponents/Base.h"
#include "ThingComponents/HeroStats.h"
#include "ThingComponents/CreatureModeManager.h"
#include "ThingComponents/PhysicsBase.h"
#include "ThingComponents/ParticleEmitter.h"
#include "ThingComponents/Hero.h"
#include "ThingComponents/HeroMorph.h"
#include "ThingComponents/Combat.h"
#include "ThingComponents/Wife.h"
#include "ThingComponents/Followed.h"
#include "ThingComponents/RegionFollower.h"
#include "ThingComponents/CreatureAI.h"
#include "ThingComponents/AIScratchPad.h"
#include "ThingComponents/HeroOpinionDeedLog.h"
#include "ThingComponents/Village.h"
#include "ThingComponents/VillageMember.h"
#include "ThingComponents/ActionUse.h"
#include "ThingComponents/GraphicAppearance.h"
#include "ThingComponents/InventoryClothing.h"
#include "ThingComponents/Carrying.h"
#include "ThingComponents/Enemy.h"
#include "ThingComponents/QuestCard.h"
#include "ThingComponents/ScriptedControl.h"
#include "ThingComponents/Haste.h"
#include "ThingComponents/ThingOwner.h"
#include "ThingComponents/OwnedEntity.h"
#include "ThingComponents/BuyableHouse.h"
#include "ThingComponents/Door.h"
#include "ThingComponents/InventoryItem.h"
#include "ThingComponents/Light.h"
#include "ThingComponents/InventoryAbilities.h"
#include "ThingComponents/InventoryBase.h"
#include "ThingComponents/Weapon.h"
#include "ThingComponents/ObjectAugmentations.h"
#include "ThingComponents/HeroReceiveItems.h"
#include "ThingComponents/Look.h"
#include "ThingComponents/Chest.h"

#include "Creature.h"

enum eMovementTypes {
	ST_SLOW_WALK,
	ST_WALK,
	ST_JOG,
	ST_RUN,
	ST_SPRINT,
	STANDARD_FLY,
	TOTAL_MOVEMENT_TYPES
};

class CTCRegionDisplay;
class CThingSearchTools;
class CWorldMap;
class CPlayer;
class CThingManager;

class CThing {
public:
	char pad[0xB0];
	float m_fMaxHealth;
	float m_fHealth;

    static CThingManager* GetCurrentThingManager();
    const CPlayer* PeekPlayer();
	CTCBase* GetTC(ETCInterfaceType id);
    CTCBase* AddTC(CCharString* name, int voverride, int pparams_base);
    bool HasTC(ETCInterfaceType id);
    void RemoveTC(ETCInterfaceType id);
	CVector* GetPosition();
    static int GetThingID(char* name);
    ECreatureType GetCreatureType();
    static CWorldMap* GetWorldMap();
    CDefString* GetDefName();
    ECreatureProperty GetCreatureProperty();
    CThingSearchTools* GetThingSearchTools();

    void LockAllDoors(bool lock, bool avoid_hero);
    void Kill(bool perform);
    bool isThingAlive();
    void SetInLimbo(bool on);
    bool IsChild();
    void SetNewBrain(int brain_def);
    int GetActionID();
    void ClearQueuedActions();
    void FinishCurrentAction();
    bool SetCurrentAction(CTCBase* action);
    bool IsFreeToPerformAction(CTCBase* action);
    bool HasPrecedingAction();
    void LearnAbility(EHeroAbility ability, bool learn, int quick_access_slot, bool silent);
    void LearnExpression(CCharString* expression_name, int quick_access_slot, bool silent);
};

int GetThingID(char* name);

CThing* __fastcall CreateThing(int id, CVector* pos, int plr, int unk, int unk2, char* name);
CThing* __fastcall CreateCreature(int id, CVector* pos, int plr);


class CThingManager {

};