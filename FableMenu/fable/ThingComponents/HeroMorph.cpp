#include "HeroMorph.h"
#include "../../core.h"

void CTCHeroMorph::AddTatoo(int tatoo_def_index)
{
	CallMethod<0x71DA70, CTCHeroMorph*, int>(this, tatoo_def_index);
}

bool CTCHeroMorph::HasAnyTatoos()
{
	return CallMethodAndReturn<bool, 0x71BE00, CTCHeroMorph*>(this);
}

void CTCHeroMorph::RemoveAllTatoos()
{
	CallMethod<0x71CE30, CTCHeroMorph*>(this);
}