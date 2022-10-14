#pragma once
#include "Thing.h"

class CIntelligentPointer {
public:
	int  vTable;
	int  Pointer;

	CIntelligentPointer(CThing*);

	CThing* operator *();
};