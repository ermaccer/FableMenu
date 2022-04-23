#include "eSettingsManager.h"
#include "IniReader.h"

eSettingsManager* SettingsMgr = new eSettingsManager;

void eSettingsManager::Init()
{
	CIniReader ini("");
	iMenuOpenKey = ini.ReadInteger("Settings", "iMenuOpenKey", VK_OEM_3);
	iOverwriteConstantFPS = ini.ReadInteger("Settings", "iOverwriteConstantFPS", 15);
	bSlowMotionEffectsEverything = ini.ReadBoolean("Settings", "bSlowMotionEveywhere", false);
	bUseBuiltInWindowedMode = ini.ReadBoolean("Settings", "bUseBuiltInWindowedMode", false);
	iDefaultX = ini.ReadInteger("Settings", "iDefaultXRes", 1024);
	iDefaultY = ini.ReadInteger("Settings", "iDefaultYRes", 768);
}
