#pragma once
#include "Base.h"

class CTCHero : public CTCBase {
public:
	bool m_bCanUseWeapons;
	bool m_bCanUseWill;

};

enum eExperience {
	EXPERIENCE_STRENGTH,
	EXPERIENCE_SKILL,
	EXPERIENCE_WILL,
	TOTAL_EXPERIENCE
};

class CTCHeroStats {
public:
	char pad[0x30];
	float m_fAge; 
	float m_unk; 
	float m_fFatLevel;
	int m_nGold;
	char _pad[24];
	int m_nWillPower;
	int m_nMaxWillPower; 
	char __pad[184];

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

class CTCHeroExperience : public CTCBase {
public:
	char pad[8];
	int  m_nGeneralExperience;
	int* m_pExperience;
};