#include "GameDefinitionManager.h"
#include "../core.h"

CGameDefinitionManager* CGameDefinitionManager::GetDefinitionManager()
{
	return *(CGameDefinitionManager**)0x13B879C;
}

int CGameDefinitionManager::GetDefGlobalIndexFromName(CCharString* name)
{
	return CallMethodAndReturn<int, 0x9AD410, CGameDefinitionManager*, CCharString*>(this, name);
}

CDefString* CGameDefinitionManager::GetDefNameFromGlobalIndex(CDefString* result, int def_index)
{
	return CallMethodAndReturn<CDefString*, 0x9ACCC0, CGameDefinitionManager*, CDefString*, int>(this, result, def_index);
}

int* CGameDefinitionManager::GetBrainDef(CCharString* def_name, int* result)
{
	return CallMethodAndReturn<int*, 0x669770, CGameDefinitionManager*, CCharString*, int*>(this, def_name, result);
}

void CGameDefinitionManager::GetOpinionPersonalitDef(int def_index, int* result)
{
	CallMethod<0x79BD80, CGameDefinitionManager*, int, int[]>(this, def_index, result);
}