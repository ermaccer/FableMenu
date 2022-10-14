#pragma once
#include "Hero.h"
#include "FCore.h"
#include "Creature.h"

class CTCEnemy;
class CTCRegionFollower;

class CThing {
public:
	char pad[0xB0];
	float m_fMaxHealth;
	float m_fHealth;

	CTCHeroStats* GetHeroStats();
	CTCHeroMorph* GetHeroMorph();
	CTCHeroExperience* GetHeroExperience();
	CTCHero* GetHero();
	CTCEnemy* GetEnemy();
	CTCRegionFollower* GetRegionFollower();


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


CThing* __fastcall CreateThing(int id, CVector* pos, int plr, int unk, int unk2, char* name);

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

CThing* __fastcall CreateCreature(int id, CVector* pos, int plr);