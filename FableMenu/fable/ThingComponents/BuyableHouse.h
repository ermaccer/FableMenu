#pragma once
#include "HeroStats.h"

class CTCBuyableHouse {
public:
	void Evict();
	bool HasDummyVillagers();
	bool isBuildingBeingUsed(bool ignore_homebuilding);
	void SetOwnedByPlayer(CTCHeroStats* hero_stats);
	void SetRented(int val);
	void CountMoneyBags();
};