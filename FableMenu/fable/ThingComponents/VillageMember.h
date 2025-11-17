#pragma once
#include "Village.h"

class CThing;

class CTCVillageMember {
public:
	CTCVillage* GetPVillage();
	bool IsAttachedToVillage();
};