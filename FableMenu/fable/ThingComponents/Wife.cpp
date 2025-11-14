#include "Wife.h"
#include "../../core.h"

void CTCWife::Marry(CTCHeroStats* instance_with_no_cutscene = 0)
{
	CallMethod<0x6D18A0, CTCWife*, bool>(this, instance_with_no_cutscene);
}

void CTCWife::Divorce()
{
	CallMethod<0x6D0180, CTCWife*>(this);
}

void CTCWife::HaveSex()
{
	CallMethod<0x6CF920, CTCWife*>(this);
}

bool CTCWife::IsMarriedToThePlayer()
{
	return CallMethodAndReturn<bool, 0x6CEC80, CTCWife*>(this);
}