#pragma once
#include <Windows.h>

// as usual, pluginmh/mugenhook

class eSettingsManager {
public:
	void Init();

	int iMenuOpenKey = VK_OEM_3;
	int iOverwriteConstantFPS = 15;
	int  iDefaultX;
	int  iDefaultY;
	bool bSlowMotionEffectsEverything = false;
	bool bUseBuiltInWindowedMode = false;


};

extern eSettingsManager* SettingsMgr;