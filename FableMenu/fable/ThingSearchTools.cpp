#include "ThingSearchTools.h"
#include "../core.h"

std::list<CThing*>* CThingSearchTools::PeekTypeList(int type)
{
	return CallMethodAndReturn<std::list<CThing*>*, 0x49C780, CThingSearchTools*, int>(this, type);
}