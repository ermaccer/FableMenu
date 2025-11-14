#include "OwnedEntity.h"
#include "../../core.h"

int CTCOwnedEntity::GetPOwner()
{
	return *(int*)((char*)this + 0xD);
}

void CTCOwnedEntity::SetPOwner(int owner)
{
	CallMethod<0x7E8590, CTCOwnedEntity*, int>(this,owner);
}