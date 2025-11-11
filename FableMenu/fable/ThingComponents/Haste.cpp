#include "Haste.h"
#include "../../core.h"

float CTCHaste::GetActionSpeedMultiplier()
{
	return CallMethodAndReturn<float, 0x7FFFB0, CTCHaste*>(this);
}

void CTCHaste::SetActionSpeedMultiplier(void* pcaller, float speed)
{
	CallMethod<0x5812AE, CTCHaste*, void*, float>(this, pcaller, speed);
}

void CTCHaste::UnsetActionSpeedMultiplier(void* pcaller)
{
	CallMethod<0x58148D, CTCHaste*, void*>(this, pcaller);
}