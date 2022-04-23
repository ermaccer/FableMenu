#pragma once
#include "Base.h"

class CTCHero : public CTCBase {
public:
	bool m_bCanUseWeapons;
	bool m_bCanUseWill;

};

class CTCHeroStats {
public:
	char pad[0x30];
	float m_fAge; 
	float m_unk; 
	float m_fFatLevel;
	int m_nGold;
};

class CTCHeroMorph {
public:
	char pad[0x3D];
	bool m_bUpdate;
	float m_fStrength;
	float m_fBerserk;
	float m_fWill;
	float m_fSkill;
	float m_fAge;
	float m_fAlign;
	float m_fFat;
	float m_fUnk;
	bool  m_bKid;
};