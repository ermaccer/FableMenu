#include "Weapon.h"
#include "../../core.h"

float CTCWeapon::GetDamage()
{
	return CallMethodAndReturn<float, 0x5DAAA0, CTCWeapon*>(this);
}

bool CTCWeapon::IsMeleeWeapon()
{
	return CallMethodAndReturn<bool, 0x5DAA00, CTCWeapon*>(this);
}

bool CTCWeapon::IsProjectileWeapon()
{
	return CallMethodAndReturn<bool, 0x5DAA40, CTCWeapon*>(this);
}