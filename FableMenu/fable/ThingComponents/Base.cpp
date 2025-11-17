#include "Base.h"
#include "../../core.h"

CPlayerManager* CTCBase::GetPlayerManager()
{
	return CallMethodAndReturn<CPlayerManager*, 0x686D40, CTCBase*>(this);
}

bool CTCBase::IsSerialisableForHeroState()
{
	return CallMethodAndReturn<bool, 0xD42FE0, CTCBase*>(this);
}

void CTCBase::AddTC(CCharString* name)
{
	CallMethod<0x686A50, CTCBase*, CCharString*>(this, name);
}