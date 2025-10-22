#include "CCreatureAction_AddRealObjectToInventory.h"
#include "../../core.h"

CCreatureAction_AddRealObjectToInventory::CCreatureAction_AddRealObjectToInventory(CCreatureAction_AddRealObjectToInventory* addObject, CThing* creature, CThing* object)
{
	CallMethod<0x7EB2D0, CCreatureAction_AddRealObjectToInventory*, CThing*, CThing*>(addObject, creature, object);
}