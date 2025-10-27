#pragma once
#include <vector>
#include "../FCore.h"

class CTCObjectAugmentations
{
public:
	int GetNumberOfSlots();
	float GetDamageMultiplier();
	float GetExperienceMultiplier();
	int GetStaminaToAddThisFrame();
	int GetHealthToAddThisFrame();
	int GetFreeSlot();

	CWideString* GetAugmentationNameInSlot(CWideString* result, int slot);
	bool HasAugmentationInSlot(int slot);

	void GetAugmentations(std::vector<int>* augmentations);
	void AddNewSlot();
	void AttachAugmentationToSlot(int augmentation_def_index, int slot);
	void RemoveAugmentationFromSlot(int slot);
};