#include "CreatureAction_PickUpGenericBox.h"
#include "../../core.h"

CCreatureAction_PickUpGenericBox::CCreatureAction_PickUpGenericBox(CCreatureAction_PickUpGenericBox* box, CThing* creature, CThing* thing)
{
	CallMethod<0x843700, CCreatureAction_PickUpGenericBox*, CThing*, CThing*>(box, creature, thing);
}