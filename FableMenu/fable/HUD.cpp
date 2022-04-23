#include "HUD.h"
#include "..\FableMenu.h"

bool __fastcall HUD::Display(int ptr)
{
	if (FableMenu::ms_bDisableHUD)
		return false;
	else
		return *(int*)(ptr + 660) != 1;
}

CHUD* GetHud()
{
	return *(CHUD**)0x13B8790;
}
