#pragma once
#include "../core.h"

class CAProgressDisplay;

namespace NProgressDisplay
{
	static CAProgressDisplay* PProgressDisplay = (CAProgressDisplay*)0x13CAA38;

	inline static void InitialiseProgressDisplay(CAProgressDisplay* progressDisplay)
	{
		CallMethod<0x413120, CAProgressDisplay*>(progressDisplay);
	}
};