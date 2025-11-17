#pragma once
#include "../ThingComponents/ScriptedControl.h"

class CThing;

class CCreatureAction_PickUpJugToFill : public CTCScriptedControl::CActionBase {
public:
	CCreatureAction_PickUpJugToFill(CCreatureAction_PickUpJugToFill* jug, CThing* creature, CThing* thing);
};