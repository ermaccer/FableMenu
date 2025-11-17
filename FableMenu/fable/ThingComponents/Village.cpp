#include "Village.h"
#include "../../core.h"

void CTCVillage::EnableGuards(bool enable)
{
	CallMethod<0x65C45A, CTCVillage*, bool>(this, enable);
}

void CTCVillage::EnableVillagerDefTypes(bool enable, CCharString* def_name)
{
	CallMethod<0x65B142, CTCVillage*, bool, CCharString*>(this, enable, def_name);
}

void CTCVillage::ClearCrimes()
{
	CallMethod<0x65C2D0, CTCVillage*>(this);
}

int CTCVillage::GetNumberOfGayVillagers()
{
	return CallMethodAndReturn<int, 0x658F41, CTCVillage*>(this);
}

void CTCVillage::SetVillageLimbo(bool limbo)
{
	CallMethod<0x65C36E, CTCVillage*, bool>(this, limbo);
}