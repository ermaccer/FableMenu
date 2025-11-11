#include "../../core.h"
#include "Enemy.h"

void CTCEnemy::RemoveEnemyThing(CThing* creature)
{
	CallMethod<0x76CC00, CTCEnemy*, CThing*>(this,creature);
}

void CTCEnemy::SetFaction(CCharString* str)
{
	CallMethod<0x76C810, CTCEnemy*, CCharString*>(this, str);
}

void CTCEnemy::AddAlly(CThing* creature)
{
	CallMethod<0x76D270, CTCEnemy*, CThing*>(this, creature);
}

bool CTCEnemy::IsEnemyOf(CThing* creature)
{
	return CallMethodAndReturn<bool, 0x76CCE0, CTCEnemy*, CThing*>(this, creature);
}