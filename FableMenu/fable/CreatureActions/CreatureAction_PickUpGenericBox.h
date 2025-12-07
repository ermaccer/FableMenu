#pragma once
#include "../FCore.h"
#include "../ThingComponents/ScriptedControl.h"

class CThing;

class CCreatureAction_PickUpGenericBox : public CTCScriptedControl::CActionBase {
public:
	CCreatureAction_PickUpGenericBox(CCreatureAction_PickUpGenericBox* box, CThing* creature, CThing* thing);
};