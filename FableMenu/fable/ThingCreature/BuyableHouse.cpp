#include "BuyableHouse.h"
#include "../../core.h"

void CTCBuyableHouse::Evict()
{
	CallMethod<0x6C0FD0, CTCBuyableHouse*>(this);
}

bool CTCBuyableHouse::HasDummyVillagers()
{
	return CallMethodAndReturn<bool, 0x8D3350, CTCBuyableHouse*>(this);
}

void CTCBuyableHouse::SetOwnedByPlayer(CTCHeroStats* hero_stats)
{
	CallMethod<0x6C17B0, CTCBuyableHouse*,CTCHeroStats*>(this, hero_stats);
}

bool CTCBuyableHouse::isBuildingBeingUsed(bool ignore_homebuilding)
{
	return CallMethodAndReturn<bool,0x6BFB10, CTCBuyableHouse*,bool>(this, ignore_homebuilding);
}

void CTCBuyableHouse::SetRented(int val)
{
	CallMethod<0x6C17B0, CTCBuyableHouse*, int>(this, val);
}

void CTCBuyableHouse::CountMoneyBags()
{
	CallMethod<0x6C04D0, CTCBuyableHouse*>(this);
}