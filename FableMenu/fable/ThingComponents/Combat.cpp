#include "Combat.h"
#include "../../core.h"

void CTCCombat::SetCombatType(int* combat_def)
{
	CallMethod<0x7355F0, CTCCombat*, int*>(this, combat_def);
}