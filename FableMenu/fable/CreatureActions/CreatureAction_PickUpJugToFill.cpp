#include "CreatureAction_PickUpJugToFill.h"
#include "../../core.h"

CCreatureAction_PickUpJugToFill::CCreatureAction_PickUpJugToFill(CCreatureAction_PickUpJugToFill* jug, CThing* creature, CThing* thing)
{
	CallMethod<0x844140, CCreatureAction_PickUpJugToFill*, CThing*, CThing*>(jug, creature, thing);
}