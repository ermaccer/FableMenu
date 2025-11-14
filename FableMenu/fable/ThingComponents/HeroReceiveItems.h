#pragma once
#include "../FCore.h"

class CThing;

class CTCHeroReceiveItems {
public:
	char pad[0x26];
	bool m_bDisplayItems;
	void PrepareToShowItems(CVector* pos);
};