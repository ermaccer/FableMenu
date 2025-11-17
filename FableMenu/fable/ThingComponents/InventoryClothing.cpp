#include "InventoryClothing.h"
#include "../../core.h"

void CTCInventoryClothing::RemoveAllClothing()
{
	CallMethod<0x5B40E6, CTCInventoryClothing*>(this);
}

void CTCInventoryClothing::OpenInventory()
{
	CallMethod<0x5B4E7C, CTCInventoryClothing*>(this);
}

void CTCInventoryClothing::CloseInventory()
{
	CallMethod<0x5B6A2D, CTCInventoryClothing*>(this);
}