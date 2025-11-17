#include "InventoryBase.h"
#include "../../core.h"

char CTCInventoryBase::AddItemToInventory(CThing* item, bool add_selected, bool add_quick_access, int price_bought_for, bool silent)
{
	return CallMethodAndReturn<char, 0x5BF654, CTCInventoryBase*, CThing*, bool, bool, int, bool>(this, item, add_selected, add_quick_access, price_bought_for, silent);
}