#include "Carrying.h"
#include "../../core.h"

CTCCarrying* CTCCarrying::Alloc(CThing* creature)
{
	CallMethodAndReturn<CTCCarrying*, 0x4E7DFC, CThing*>(creature);
}

bool CTCCarrying::IsCarryingWeapon(CThing* creature)
{
	return FASTCallAndReturn<bool, 0x6A1540, CThing*>(creature);
}

bool CTCCarrying::IsCarryingThing(int slot)
{
	return CallMethodAndReturn<bool, 0x6A10A0, int>(slot);
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
	return CallMethodAndReturn<CThing*, 0x6A11F0, CTCCarrying*, int>(this, slot);
}

CThing* CTCCarrying::GetCarriedThing(int def_index)
{
	return CallMethodAndReturn<CThing*, 0x6A1120, CTCCarrying*, int>(this, def_index);
}

CThing* CTCCarrying::GetThingInPrimarySlot()
{
	return CallMethodAndReturn<CThing*, 0x6A1440, CTCCarrying*>(this);
}

bool CTCCarrying::IsCarrySlotFree(int slot)
{
	return CallMethodAndReturn<bool, 0x6A1230, CTCCarrying*, int>(this, slot);
}

int CTCCarrying::GetCarrySlotActive()
{
	return CallMethodAndReturn<int, 0x705CC0, CTCCarrying*>(this);
}