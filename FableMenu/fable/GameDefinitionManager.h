#pragma once
#include "FCore.h"

class CGameDefinitionManager {
public:
	static CGameDefinitionManager* GetDefinitionManager();
	int GetDefGlobalIndexFromName(CCharString* name);
	CCharString* GetDefNameFromGlobalIndex(CCharString* result, int def_index);

	void GetOpinionPersonalitDef(int def_index, int* result);
	int* GetBrainDef(CCharString* def_name, int* result);
};
