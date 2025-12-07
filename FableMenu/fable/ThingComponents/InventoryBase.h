#pragma once

class CThing;

class CTCInventoryBase {
public:
	char AddItemToInventory(CThing* item, bool add_selected, bool add_quick_access, int price_bought_for, bool silent);
};
