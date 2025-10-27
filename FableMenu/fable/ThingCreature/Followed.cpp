#include "../../core.h"
#include "Followed.h"


CTCFollowed* CTCFollowed::Alloc(CThing* thing)
{
	return CallMethodAndReturn<CTCFollowed*, 0x4D5245, CThing*>(thing);
}

void CTCFollowed::AddFollower(CThing* follower,bool is_ai_follower)
{
	CallMethod<0x6D50C0, CTCFollowed*, CThing*, bool>(this, follower, is_ai_follower);
}

void CTCFollowed::RemoveFollower(CThing* thing)
{
	CallMethod<0x6D5180, CTCFollowed*, CThing*>(this, thing);
}

void CTCFollowed::AddEmoteIcon(CThing* thing)
{
	CallMethod<0x6D4FD0, CTCFollowed*, CThing*>(this, thing);
}

void CTCFollowed::RemoveEmoteIcon(CThing* thing)
{
	CallMethod<0x6D5050, CTCFollowed*, CThing*>(this, thing);
}
