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
	CTCHero* GetHero();


	CVector* GetPosition();
};


CThing* __fastcall CreateThing(int id, CVector* pos, int plr, int unk, int unk2, char* name);

int GetThingID(char* name);