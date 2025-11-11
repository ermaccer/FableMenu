#include "QuestCard.h"
#include "../../core.h"

bool CTCQuestCard::IsCore()
{
	return CallMethodAndReturn<bool, 0x702280, CTCQuestCard*>(this);
}

bool CTCQuestCard::IsExclusive()
{
	return CallMethodAndReturn<bool, 0x7022A0, CTCQuestCard*>(this);
}

bool CTCQuestCard::IsActivable()
{
	return CallMethodAndReturn<bool, 0x702810, CTCQuestCard*>(this);
}

bool CTCQuestCard::IsVignette()
{
	return CallMethodAndReturn<bool, 0x7022E0, CTCQuestCard*>(this);
}

bool CTCQuestCard::IsOptional()
{
	return CallMethodAndReturn<bool, 0x7022C0, CTCQuestCard*>(this);
}

bool CTCQuestCard::IsRouteToAppearOnMinimap()
{
	return CallMethodAndReturn<bool, 0x7022F0, CTCQuestCard*>(this);
}

CWideString* CTCQuestCard::GetQuestName(CWideString* result)
{
	return CallMethodAndReturn<CWideString*, 0x702310, CTCQuestCard*, CWideString*>(this, result);
}

CCharString* CTCQuestCard::GetTeleporterRegionName(CCharString* result)
{
	return CallMethodAndReturn<CCharString*, 0x7021F0, CTCQuestCard*, CCharString*>(this, result);
}