#include "Pointer.h"
#include "..\core.h"

CIntelligentPointer::CIntelligentPointer(CThing* thing)
{
	vTable = *(int*)0x123E7E0;
	Pointer = 0;

	CallMethod<0xA01B90, CIntelligentPointer*, CThing*>(this, thing);
}

CThing* CIntelligentPointer::operator*()
{
	return CallMethodAndReturn<CThing*, 0xA01B50, CIntelligentPointer*>(this);
}
