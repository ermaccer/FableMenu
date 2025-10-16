#pragma once
#include "../FCore.h"

class CTCQuestCard
{
public:
	bool IsCore();
	bool IsExclusive();
	bool IsVignette();
	bool IsOptional();
	bool IsRouteToAppearOnMinimap();

	bool IsActivable();
};