#include "Carrying.h"
#include "../../core.h"

CTCCarrying* CTCCarrying::Alloc(CThing* creature)
{
	CallMethodAndReturn<CTCCarrying*, 0x4E7DFC, CThing*>(creature);
}

bool CTCCarrying::isCarryingWeapon(CThing* creature)
{
	return FASTCallAndReturn<bool, 0x6A1540, CThing*>(creature);
}

void CTCCarrying::AddThingInCarrySlot(CThing* creature, int slot, int set_up_weapon_mode)
{
	CallMethod<0x6A1F80, CTCCarrying*, CThing*, int, int>(this,creature,slot,set_up_weapon_mode);
}

void CTCCarrying::RemoveThingInCarrySlot(int slot, bool update_pos_before_removal)
{
	CallMethod<0x6A16A0, CTCCarrying*, int, bool>(this, slot, update_pos_before_removal);
}

CThing* CTCCarrying::GetThingInCarrySlot(int slot)
{
	return CallMethodAndReturn<CThing*,0x6A11F0, CTCCarrying*, int>(this, slot);
}

bool CTCCarrying::IsCarrySlotFree(int slot)
{
	return CallMethodAndReturn<bool, 0x6A1230, CTCCarrying*, int>(this, slot);
}