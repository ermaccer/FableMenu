#pragma once
#include "FCore.h"

#include "ThingCreature/Base.h"
#include "ThingCreature/HeroStats.h"
#include "ThingCreature/ModeManager.h"
#include "ThingCreature/PhysicsBase.h"
#include "ThingCreature/ParticleEmitter.h"
#include "ThingCreature/Hero.h"
#include "ThingCreature/HeroMorph.h"
#include "ThingCreature/Combat.h"
#include "ThingCreature/Wife.h"
#include "ThingCreature/Followed.h"
#include "ThingCreature/RegionFollower.h"
#include "ThingCreature/CreatureAI.h"
#include "ThingCreature/AIScratchPad.h"
#include "ThingCreature/HeroOpinionLog.h"
#include "ThingCreature/Village.h"
#include "ThingCreature/VillageMember.h"
#include "ThingCreature/ActionUse.h"
#include "ThingCreature/GraphicAppearance.h"
#include "ThingCreature/InventoryClothing.h"
#include "ThingCreature/Carrying.h"
#include "ThingCreature/Enemy.h"
#include "ThingCreature/QuestCard.h"
#include "ThingCreature/ScriptedControl.h"
#include "ThingCreature/Haste.h"
#include "ThingCreature/ThingOwner.h"
#include "ThingCreature/OwnedEntity.h"
#include "ThingCreature/BuyableHouse.h"
#include "ThingCreature/Door.h"
#include "ThingCreature/InventoryItem.h"
#include "ThingCreature/Light.h"
#include "ThingCreature/InventoryAbilities.h"
#include "ThingCreature/Weapon.h"
#include "ThingCreature/ObjectAugmentations.h"

#include "CreatureActions/CreatureAction_PickUpGenericBox.h"
#include "CreatureActions/CreatureAction_PickUpJugToFill.h"
#include "CreatureActions/ActionPlayAnimation.h"
#include "CreatureActions/CreatureAction_DropWeapon.h"

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
	CTCBase* GetTC(int id);
	CTCHeroExperience* GetHeroExperience();
	CTCHero* GetHero();
	CTCEnemy* GetEnemy();
	CTCLook* GetLook();
	CTCScriptedControl* GetSC();
	CVector* GetPosition();
    CTCBase* AddTC(CCharString* name, int voverride, int pparams_base);
    static int GetThingID(char* name);
    ECreatureType GetCreatureType();
    static CWorldMap* GetWorldMap();
    CDefString* GetDefName();
    ECreatureProperty GetCreatureProperty();
    CThingSearchTools* GetThingSearchTools();
    CTCCreatureModeManager* GetCreatureModeManager();
    CTCDParticleEmitter* GetParticleEmitter();
    CTCPhysicsStandard* GetPhysicsStandard();
    CTCCombat* GetCombat();
    CTCHeroMorph* GetHeroMorph();
    CTCHeroStats* GetHeroStats();
    CTCFollowed* GetFollowed();
    CreatureAI* GetCreatureAI();
    CTCAIScratchPad* GetAIScratchPad();
    CTCRegionFollower* GetRegionFollower();
    CTCHeroOpinionLog* GetHeroOpinionLog();
    CTCScriptedControl* GetScriptedControl();
    CTCActionUse* GetActionUse();
    CTCVillage* GetVillage();
    CTCVillageMember* GetVillageMember();
    CTCWife* GetWife();
    CTCGraphicAppearance* GetGraphicAppearance();
    CTCInventoryClothing* GetInventoryClothing();
    CTCCarrying* GetCarrying();
    CTCThingOwner* GetThingOwner();
    CTCOwnedEntity* GetOwnedEntity();
    CTCBuyableHouse* GetBuyableHouse();
    CTCHaste* GetHaste();
    CTCQuestCard* GetQuestCard();
    CTCDoor* GetDoor();
    CTCInventoryItem* GetInventoryItem();
    CTCLight* GetLight();
    CTCInventoryAbilities* GetInventoryAbilities();
    CTCObjectAugmentations* GetObjectAugmentations();
    CTCWeapon* GetWeapon();

    void LockAllDoors(bool lock, bool avoid_hero);
    void Kill(bool perform);
    bool IsChild();
    void SetNewBrain(int brain_def);
    bool HasTC(int interface_type);
    void RemoveTC(ETCInterfaceType id);
    int GetActionID();
    void ClearQueuedActions();
    void FinishCurrentAction();
    bool SetCurrentAction(CTCBase* action);
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
