#include "RegionFollower.h"
#include "../../core.h"

CTCRegionFollower* CTCRegionFollower::Alloc(CThing* thing)
{
	return CallMethodAndReturn<CTCRegionFollower*, 0x6AED80, CThing*>(thing);
}

void CTCRegionFollower::AddFollower(CThing* thing)
{
	CallMethod<0x6AEDC0, CTCRegionFollower*,CThing*>(this,thing);
}

void CTCRegionFollower::RemoveFollower(CThing* thing)
{
	CallMethod<0x6AEBA0, CTCRegionFollower*,CThing*>(this,thing);
}