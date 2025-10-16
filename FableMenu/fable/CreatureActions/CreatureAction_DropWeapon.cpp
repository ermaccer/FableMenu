#include "CreatureAction_DropWeapon.h"
#include "../../core.h"

CCreatureAction_DropWeapon::CCreatureAction_DropWeapon(CCreatureAction_DropWeapon* drop, CThing* creature)
{
	CallMethod<0x7ECFD0, CCreatureAction_DropWeapon*, CThing*>(drop, creature);
}