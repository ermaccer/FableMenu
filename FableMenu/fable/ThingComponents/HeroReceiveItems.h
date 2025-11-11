#pragma once
#include <list>
class CVector;
class CThing;

class CTCHeroReceiveItems {
public:
	char pad[0x26];
	bool displayingItems;
	void PrepareToShowItems(CVector* pos);
};