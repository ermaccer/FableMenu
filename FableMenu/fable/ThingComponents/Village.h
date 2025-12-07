#pragma once
#include "../FCore.h"

class CThing;

class CTCVillage {
public:
	void EnableGuards(bool enable);
	void EnableVillagerDefTypes(bool enable, CCharString*  def_name);
	int GetNumberOfGayVillagers();
	void ClearCrimes();
	void SetVillageLimbo(bool limbo);
};