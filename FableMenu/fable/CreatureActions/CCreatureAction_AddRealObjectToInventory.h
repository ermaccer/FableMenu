#include "../FCore.h"
#include "../ThingCreature/ScriptedControl.h"

class CThing;

class CCreatureAction_AddRealObjectToInventory : public CTCScriptedControl::CActionBase {
public:
	CCreatureAction_AddRealObjectToInventory(CCreatureAction_AddRealObjectToInventory* addObject, CThing* creature, CThing* object);
};