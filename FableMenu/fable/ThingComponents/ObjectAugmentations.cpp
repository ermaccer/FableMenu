#include "ObjectAugmentations.h"
#include "../../core.h"

int CTCObjectAugmentations::GetNumberOfSlots()
{
	return CallMethodAndReturn<int, 0x765D80, CTCObjectAugmentations*>(this);
}

void CTCObjectAugmentations::GetAugmentations(std::vector<int>* augmentations)
{
	CallMethod<0x766920, CTCObjectAugmentations*, std::vector<int>*>(this, augmentations);
}

CWideString* CTCObjectAugmentations::GetAugmentationNameInSlot(CWideString* result, int slot)
{
	return CallMethodAndReturn<CWideString*, 0x765E70, CTCObjectAugmentations*, CWideString*, int>(this, result, slot);
}

float CTCObjectAugmentations::GetDamageMultiplier()
{
	return CallMethodAndReturn<float, 0x766140, CTCObjectAugmentations*>(this);
}

float CTCObjectAugmentations::GetExperienceMultiplier()
{
	return CallMethodAndReturn<float, 0x766400, CTCObjectAugmentations*>(this);
}

int CTCObjectAugmentations::GetStaminaToAddThisFrame()
{
	return CallMethodAndReturn<int, 0x766330, CTCObjectAugmentations*>(this);
}

int CTCObjectAugmentations::GetHealthToAddThisFrame()
{
	return CallMethodAndReturn<int, 0x766260, CTCObjectAugmentations*>(this);
}

int CTCObjectAugmentations::GetFreeSlot()
{
	return CallMethodAndReturn<int, 0x765D50, CTCObjectAugmentations*>(this);
}

bool CTCObjectAugmentations::HasAugmentationInSlot(int slot)
{
	return CallMethodAndReturn<bool, 0x765DA0, CTCObjectAugmentations*, int>(this, slot);
}

void CTCObjectAugmentations::AddNewSlot()
{
	CallMethod<0x766D70, CTCObjectAugmentations*>(this);
}

void CTCObjectAugmentations::AttachAugmentationToSlot(int augmentation_def_index, int slot)
{
	CallMethod<0x768120, CTCObjectAugmentations*, int, int>(this, augmentation_def_index, slot);
}

void CTCObjectAugmentations::RemoveAugmentationFromSlot(int slot)
{
	CallMethod<0x7681D0, CTCObjectAugmentations*, int>(this, slot);
}