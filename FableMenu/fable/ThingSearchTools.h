#pragma once
#include "FCore.h"

class CThing;

class CThingSearchTools {
public:
	std::list<CThing*>* PeekTypeList(int type);
};