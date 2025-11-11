#include "InventoryItem.h"
#include "../../core.h"

void CTCInventoryItem::RemoveFromInventory()
{
	CallMethod<0x5D8E20, CTCInventoryItem*>(this);
}

bool CTCInventoryItem::IsWeapon(int def_index)
{
	return CallMethodAndReturn<bool, 0x5D97F0, CTCInventoryItem*, int>(this, def_index);
}