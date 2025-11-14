#include "ThingOwner.h"
#include "../../core.h"

void CTCThingOwner::RemoveOwnedObject(CThing* object)
{
	CallMethod<0x71B1B0, CTCThingOwner*, CThing*>(this,object);
}