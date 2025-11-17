#pragma once
#include "FCore.h"

class CWorldMap {
public:
	enum ELoadType 
	{
		WAIT_FOR_LOAD,
		DONT_WAIT_FOR_LOAD
	};

	void ReloadCurrentRegion();
	bool IsLoadingAnyMap();
	bool IsMapLoaded(int index);
	void LoadRegion(int index, ELoadType load_type, bool load_navigation);
	void UnloadRegion(int index, bool save_things);
	void SetPlayerPos(int player, CVector* pos, ELoadType load_type);
};