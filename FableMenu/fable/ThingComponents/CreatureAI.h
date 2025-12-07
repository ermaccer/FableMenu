#pragma once
#include "../FCore.h"

class CThing;
class CAIBrain;

struct CreatureAI
{
	int field_0;
	int field_4;
	CCharString* name;
	CCharString* str;
	bool IsPlayer;
	bool Draw;
	bool unk[2];
	int homeBuilding;
	int workBuilding;
};

class CAIBrain {
public:

};