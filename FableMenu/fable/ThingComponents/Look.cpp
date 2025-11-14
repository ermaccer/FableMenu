#include "Look.h"
#include "../../core.h"

void CTCLook::GetHeadLocation(CVector* out)
{
	CallMethod<0x751B30, CTCLook*, CVector*>(this, out);
}