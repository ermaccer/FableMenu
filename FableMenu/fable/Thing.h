#pragma once
#include "FCore.h"

#include "ThingComponents/Base.h"
#include "ThingComponents/HeroStats.h"
#include "ThingComponents/ModeManager.h"
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
#include "ThingComponents/HeroOpinionLog.h"
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

#include "CreatureActions/CreatureAction_PickUpGenericBox.h"
#include "CreatureActions/CreatureAction_PickUpJugToFill.h"
#include "CreatureActions/ActionPlayAnimation.h"
#include "CreatureActions/CreatureAction_DropWeapon.h"
#include "CreatureActions/CCreatureAction_AddRealObjectToInventory.h"

enum eMovementTypes {
	ST_SLOW_WALK,
	ST_WALK,
	ST_JOG,
	ST_RUN,
	ST_SPRINT,
	STANDARD_FLY,
	TOTAL_MOVEMENT_TYPES
};

enum NCreatureMode
{
    MODE_NULL,
    MODE_STAND,
    MODE_STAND_HAPPY,
    MODE_STAND_BORED,
    MODE_CARRYING_WEAPON_STAND,
    MODE_CARRYING_PLATE_STAND,
    MODE_CARRYING_GOODS_STAND,
    MODE_SNEAK,
    MODE_SIT_CHAIR,
    MODE_SIT_BENCH,
    MODE_SIT_FLOOR,
    MODE_SIT_TAVERN_STOOL,
    MODE_BLOCK,
    MODE_SLEEP_BED,
    MODE_COOK,
    MODE_SCARED,
    MODE_OUTRAGED,
    MODE_CREEPING,
    MODE_CHEERING,
    MODE_HECKLING,
    MODE_SAD,
    MODE_ATTRACTED,
    MODE_HERO_IMITATION,
    MODE_CURIOUS,
    MODE_BULLY,
    MODE_STRAFE,
    MODE_HOVER,
    MODE_CONVERSATION,
    MODE_STAND_IN_ALL_DIRECTIONS,
    MODE_STUNNED,
    MODE_UNDERGROUND,
    MODE_KNOCKED_DOWN,
    MODE_FORCE_PUSHED,
    MODE_FISHING,
    MODE_CARRYING_GENERIC_BOX,
    MODE_BATTLE_CHARGE,
    MODE_BERSERK,
    MODE_ASSASSIN_RUSH,
    MODE_WADING,
    MODE_DRINKING_FROM_TANKARD,
    MODE_EATING_AT_TABLE,
    MODE_HOLD_JUG,
    MODE_SERVE_CUSTOMER,
    MODE_FILL_JUG,
    MODE_DRUNK,
    MODE_ARMS_OFF_TABLE,
    MODE_HANDS_BOUND,
    MODE_SCORPION_KING_TAIL_PLUNGE,
    MODE_JACK_OF_BLADES_SUMMON,
    MODE_JACK_OF_BLADES_FLOAT,
    MODE_JACK_OF_BLADES_FLASH,
    MODE_JACK_OF_BLADES_SCREAM,
    MODE_JACK_OF_BLADES_VULNERABLE,
    MODE_JACK_OF_BLADES_DEATH,
    MODE_THUNDER_LIGHTNING_STORM,
    MODE_SCORPION_KING_VULNERABLE,
    MODE_SCORPION_KING_EXHAUSTED,
    MODE_CREATURE_IS_PROJECTILE,
    MODE_ROCK_TROLL_VULNERABLE,
    MODE_GUILDMASTER_CONCENTRATE,
    MODE_GUILDMASTER_POWERUP_HEAL,
    MODE_GUILDMASTER_POWERUP_SHIELD,
    MODE_GUILDMASTER_POWERUP_SPEED,
    MODE_BRIAR_ROSE_CONCENTRATE,
    MODE_BRIAR_ROSE_INVULNERABLE,
    MODE_BRIAR_ROSE_INTANGIBLE,
    MODE_EXPLOSIVE_FORCE_PUSHED,
    MODE_DAZED,
    MODE_SCREAMER_AGGRESSIVE,
    MODE_DRAINED,
    MODE_ROLL,
    MODE_DRAGON_HOVER,
    MODE_DRAGON_SWOOP,
    MODE_DRAGON_DEFAULT,
    MODE_DRAGON_REAR_UP,
    MODE_DRAGON_FIRE_BEAM,
    MODE_DRAGON_STRAFE,
    MODE_DRAGON_STRAFE_BURNINATE,
    MODE_DRAGON_LANDED,
    MODE_DRAGON_GET_HIT,
    MODE_DRAGON_FLYING,
    MODE_INTANGIBLE,
    MODE_DRAGON_HOVER_NAPALM_GROUND,
    MODE_VULNERABLE,
    MODE_UNDERWATER,
    MODE_DRAGON_HOVER_CHARGE_UP_NAPALM_GROUND,
    MODE_CAGED,
    MODE_SCRIPTED,
    MODE_BASIC,
    MODE_SUMMONER_SUMMON,
    MODE_SUMMONER_LIGHTNING_ORB,
    MODE_CHARGE_FORCE_PUSH,
    MODE_SUMMONER_DIE,
    MODE_ICE_TROLL_ICICLE_ASSAULT,
    MODE_SCREAMER_SUPER_ATTACK,
    MODE_HIT_BY_EPIC_SPELL
};

enum ECreatureType {
    NOT_HUMAN,
    HUMAN_CHILD,
    HUMAN_ADULT,
    HUMAN_ELDERLY,
};

enum ECreatureProperty {
    THING_CREATURE_PROPERTY_NULL,
    THING_CREATURE_PROPERTY_IS_MINION,
    THING_CREATURE_PROPERTY_ANNOYABLE_BY_KIDS,
    THING_CREATURE_PROPERTY_GUARD,
    THING_CREATURE_PROPERTY_FIREFLY
};

class CTCLook;
class CThingSearchTools;
class CWorldMap;
class CPlayer;
class CThingManager {};

class CThing {
public:
	char pad[0xB0];
	float m_fMaxHealth;
	float m_fHealth;

    static CThingManager* GetCurrentThingManager();
    const CPlayer* PeekPlayer();
	CTCBase* GetTC(ETCInterfaceType id);
    CTCBase* AddTC(CCharString* name, int voverride, int pparams_base);
	CVector* GetPosition();
    static int GetThingID(char* name);
    ECreatureType GetCreatureType();
    static CWorldMap* GetWorldMap();
    CDefString* GetDefName();
    ECreatureProperty GetCreatureProperty();
    CThingSearchTools* GetThingSearchTools();
    CreatureAI* GetCreatureAI();

    void LockAllDoors(bool lock, bool avoid_hero);
    void Kill(bool perform);
    bool isThingAlive();
    void SetInLimbo(bool on);
    bool IsChild();
    void SetNewBrain(int brain_def);
    bool HasTC(ETCInterfaceType id);
    void RemoveTC(ETCInterfaceType id);
    int GetActionID();
    void ClearQueuedActions();
    void FinishCurrentAction();
    bool SetCurrentAction(CTCBase* action);
    bool IsFreeToPerformAction(CTCBase* action);
    bool HasPrecedingAction();
    void LearnAbility(EHeroAbility ability, bool learn, int quick_access_slot, bool silent);
    void LearnExpression(CCharString* expression_name, int quick_access_slot, bool silent);
};

class CTCLook {
public:
	void GetHeadLocation(CVector* out);
};

int GetThingID(char* name);

CThing* __fastcall CreateThing(int id, CVector* pos, int plr, int unk, int unk2, char* name);
CThing* __fastcall CreateCreature(int id, CVector* pos, int plr);
