#pragma once
#include "Hero.h"
#include "FCore.h"
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

class CTCEnemy;
class CTCRegionFollower;
class CTCLook;
class CTCGraphicAppearance;

class CThing {
public:
	char pad[0xB0];
	float m_fMaxHealth;
	float m_fHealth;
	// 184
	CTCHeroStats* GetHeroStats();
	CTCHeroMorph* GetHeroMorph();
	CTCHeroExperience* GetHeroExperience();
	CTCHero* GetHero();
	CTCEnemy* GetEnemy();
	CTCRegionFollower* GetRegionFollower();
	CTCLook* GetLook();
	CTCGraphicAppearance* GetGraphicAppearance();

	CVector* GetPosition();
};


class CTCEnemy {
public:
	void SetFaction(CCharString* str);
	void AddAlly(CThing* thing);
};

class CTCRegionFollower {
public:
	void AddFollower(CThing* thing);
};

class CTCLook {
public:
	void GetHeadLocation(CVector* out);
};

class CTCGraphicAppearance {
public:
	void SetAlpha(char value);
	void SetColor(int* color, CTCBase* base);
	void SetScale(float value);
};



int GetThingID(char* name);

struct  CreatureAI
{
	int field_0;
	int field_4;
	CCharString* name;
	CCharString* str;
	bool IsPlayer;
	bool Draw;
	bool unk[2];
	int homeBuilding;
	int workBuilding;

};
CThing* __fastcall CreateThing(int id, CVector* pos, int plr, int unk, int unk2, char* name);
CThing* __fastcall CreateCreature(int id, CVector* pos, int plr);
