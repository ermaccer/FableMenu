#pragma once
#include "HeroStats.h"

class CThing;

class CTCWife{
public:
	static CTCWife* Alloc(CThing* thing);

	void Marry(CTCHeroStats* instance_with_no_cutscene);
	void Divorce();
	void HaveSex();
};