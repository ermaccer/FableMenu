#include "Player.h"
#include "..\core.h"

CThing* CPlayer::GetCharacterThing()
{
	return CallMethodAndReturn<CThing*, 0x487B70, CPlayer*>(this);
}

void CPlayer::AddMode(EPlayerMode mode, bool set_mode_as_only_mode)
{
	CallMethod<0x6345C0, CPlayer*, EPlayerMode, bool>(this, mode, set_mode_as_only_mode);
}

bool CPlayer::HasMode(EPlayerMode mode)
{
	return CallMethodAndReturn<bool, 0x634160, CPlayer*, EPlayerMode>(this, mode);
}

EPlayerMode CPlayer::GetCurrentMode()
{
	return CallMethodAndReturn<EPlayerMode, 0x633BE0, CPlayer*>(this);
}

void CPlayer::RemoveMode(EPlayerMode mode)
{
	CallMethod<0x634190, CPlayer*, EPlayerMode>(this, mode);
}

void CPlayer::SetAgressiveMode(bool on)
{
	CallMethod<0x487EB0, CPlayer*, bool>(this, on);
}

void CPlayer::ToggleAggressiveMode()
{
	CallMethod<0x487E90, CPlayer*>(this);
}

void CPlayer::InitCharacterAs(CCharString* def_name)
{
	CallMethod<0x48A070, CPlayer*, CCharString*>(this, def_name);
}

void CPlayer::SetControlledCreature(CThing* creature)
{
	CallMethod<0x487CF0, CPlayer*, CThing*>(this, creature);
}

void CPlayer::UninitCharacter()
{
	CallMethod<0x487BD0, CPlayer*>(this);
}

void CPlayer::DisableInput()
{
	AddMode(PLAYER_MODE_FREEZE_CONTROLS, 0);
}

void CPlayer::EnableInput()
{
	RemoveMode(PLAYER_MODE_FREEZE_CONTROLS);
}

CTCVillage* CPlayer::GetPNearestTCVillage()
{
	return CallMethodAndReturn<CTCVillage*, 0x488620, CPlayer*>(this);
}