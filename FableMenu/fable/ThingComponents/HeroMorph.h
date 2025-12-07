#pragma once

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

	void AddTatoo(int tatoo_def_index);
	bool HasAnyTatoos();
	void RemoveAllTatoos();
};