#pragma once

class CThing;

class CTCCarrying {
public:
	CTCCarrying* Alloc(CThing* creature);
	bool IsCarryingThing(int slot);
	bool IsCarryingWeapon(CThing* creature);
	void AddThingInCarrySlot(CThing* creature, int slot, int set_up_weapon_mode);
	void RemoveThingInCarrySlot(int slot, bool update_pos_before_removal);
	bool IsCarrySlotFree(int slot);
	CThing* GetThingInPrimarySlot();
	CThing* GetThingInCarrySlot(int slot);
	CThing* GetCarriedThing(int def_index);
	int GetCarrySlotActive();
};