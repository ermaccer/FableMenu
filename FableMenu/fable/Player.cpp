#include "Player.h"
#include "..\core.h"

void CPlayer::SetMode(int id, bool unk)
{
	CallMethod<0x6345C0, CPlayer*, int, bool>(this, id, unk);
}

void CPlayer::ClearMode(int id)
{
	CallMethod<0x634190, CPlayer*, int>(this, id);
}

CThing* CPlayer::GetCharacterThing()
{
	return CallMethodAndReturn<CThing*,0x487B70, CPlayer*>(this);
}

void CPlayer::DisableInput()
{
	SetMode(17, true);
}

void CPlayer::EnableInput()
{
	//ClearMode(17);
}
