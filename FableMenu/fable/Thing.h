#pragma once
#include "Hero.h"
#include "FCore.h"

class CThing {
public:
	char pad[0xB0];
	float m_fMaxHealth;
	float m_fHealth;

	CTCHeroStats* GetHeroStats();
	CTCHeroMorph* GetHeroMorph();
	CTCHeroExperience* GetHeroExperience();
	CTCHero* GetHero();


	CVector* GetPosition();
};


CThing* __fastcall CreateThing(int id, CVector* pos, int plr, int unk, int unk2, char* name);

int GetThingID(char* name);

class CreatureAI
{
public:
	char field_0;
	char field_1;
	char field_2;
	char field_3;
	char field_4;
	char field_5;
	char field_6;
	char field_7;
	int field_8;
	int field_C;
	char field_10;
	char field_11;
	char field_12;
	char field_13;
	int field_14;
	int field_18;
	char field_1C;
	char field_1D;
	char field_1E;
	char field_1F;
	int field_20;
};