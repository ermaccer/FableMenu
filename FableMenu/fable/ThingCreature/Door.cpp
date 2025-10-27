#include "Door.h"
#include "../../core.h"

void CTCDoor::Open(CTCAnimationComplex* set_physics_mesh)
{
	CallMethod<0x730C00, CTCDoor*, CTCAnimationComplex*>(this,set_physics_mesh);
}