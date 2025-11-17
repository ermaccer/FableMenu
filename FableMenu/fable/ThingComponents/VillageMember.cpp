#include "VillageMember.h"
#include "../../core.h"

CTCVillage* CTCVillageMember::GetPVillage()
{
	return CallMethodAndReturn<CTCVillage*, 0x7EE540, CTCVillageMember*>(this);
}

bool CTCVillageMember::IsAttachedToVillage()
{
	return CallMethodAndReturn<bool, 0x69CE20, CTCVillageMember*>(this);
}