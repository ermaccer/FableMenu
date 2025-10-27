#include "Wife.h"
#include "../../core.h"

CTCWife* CTCWife::Alloc(CThing* thing)
{
	return CallMethodAndReturn<CTCWife*, 0x4D3D69, CThing*>(thing);
}

void CTCWife::Marry(CTCHeroStats* instance_with_no_cutscene = 0)
{
	CallMethod<0x6D18A0, CTCWife*, bool>(this, 0);
}

void CTCWife::Divorce()
{
	CallMethod<0x6D0180, CTCWife*>(this);
}

void CTCWife::HaveSex()
{
	CallMethod<0x6CF920, CTCWife*>(this);
}