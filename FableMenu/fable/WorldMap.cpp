#include "WorldMap.h"
#include "../core.h"

void CWorldMap::ReloadCurrentRegion()
{
	CallMethod<0x5025B0, CWorldMap*>(this);
}

bool CWorldMap::IsLoadingAnyMap()
{
	return CallMethodAndReturn<bool, 0x4FB4A0, CWorldMap*>(this);
}

bool CWorldMap::IsMapLoaded(int index)
{
	return CallMethodAndReturn<bool, 0x4FC050, CWorldMap*, int>(this, index);
}

void CWorldMap::LoadRegion(int index, ELoadType load_type, bool load_navigation)
{
	CallMethod<0x500540, CWorldMap*, int, ELoadType, bool>(this, index, load_type, load_navigation);
}

void CWorldMap::UnloadRegion(int index, bool save_things)
{
	CallMethod<0x4FEEC0, CWorldMap*, int, bool>(this, index, save_things);
}

void CWorldMap::SetPlayerPos(int player, CVector* pos, ELoadType load_type)
{
	CallMethod<0x5063E0, CWorldMap*, int, CVector*, ELoadType>(this, player, pos, load_type);
}