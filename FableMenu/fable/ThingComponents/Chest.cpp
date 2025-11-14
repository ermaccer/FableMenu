#include "Chest.h"
#include "../../core.h"

void CTCChest::Open()
{
	CallMethod<0x750540, CTCChest*>(this);
}

void CTCChest::Close()
{
	CallMethod<0x7506C0, CTCChest*>(this);
}