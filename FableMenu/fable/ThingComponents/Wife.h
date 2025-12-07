#pragma once
#include "HeroStats.h"

class CThing;

class CTCWife {
public:
	void Marry(CTCHeroStats* instance_with_no_cutscene);
	void Divorce();
	void HaveSex();
	bool IsMarriedToThePlayer();
};