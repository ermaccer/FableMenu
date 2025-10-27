#pragma once
#include "../FCore.h"
#include "../ThingCreature/ScriptedControl.h"

class CThing;

class CCreatureAction_DropWeapon : public CTCScriptedControl::CActionBase {
public:
	CCreatureAction_DropWeapon(CCreatureAction_DropWeapon* drop, CThing* creature);
};