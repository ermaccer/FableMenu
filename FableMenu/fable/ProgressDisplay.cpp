#include "ProgressDisplay.h"
#include "../core.h"

CAProgressDisplay* NProgressDisplay::PProgressDisplay = (CAProgressDisplay*)0x13CAA38;

void NProgressDisplay::InitialiseProgressDisplay(CAProgressDisplay* progressDisplay)
{
	CallMethod<0x413120, CAProgressDisplay*>(progressDisplay);
}