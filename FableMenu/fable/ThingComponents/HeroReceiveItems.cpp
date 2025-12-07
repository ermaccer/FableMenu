#include "HeroReceiveItems.h"
#include "../../core.h"

void CTCHeroReceiveItems::PrepareToShowItems(CVector* pos)
{
	CallMethod<0x7CA670, CTCHeroReceiveItems*, CVector*>(this, pos);
}