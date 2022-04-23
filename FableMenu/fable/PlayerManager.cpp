#include "PlayerManager.h"
#include "..\core.h"

CPlayer* CPlayerManager::GetPlayer()
{
	return CallMethodAndReturn<CPlayer*, 0x449970, CPlayerManager*>(this);
}
