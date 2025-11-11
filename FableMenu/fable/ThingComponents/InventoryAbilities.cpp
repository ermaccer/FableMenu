#include "InventoryAbilities.h"
#include "../../core.h"

void CTCInventoryAbilities::UpgradeAbility(EHeroAbility ability)
{
	CallMethod<0x5EEEE6, CTCInventoryAbilities*, EHeroAbility>(this, ability);
}

void CTCInventoryAbilities::ForceAllAbilitesToMaxLevel()
{
	CallMethod<0x5F3E7D, CTCInventoryAbilities*>(this);
}

int CTCInventoryAbilities::GetAbilityLevel(EHeroAbility ability)
{
	return CallMethodAndReturn<int, 0x5EDE93, CTCInventoryAbilities*, EHeroAbility>(this, ability);
}