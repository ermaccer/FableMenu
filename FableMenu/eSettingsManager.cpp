#include "eSettingsManager.h"
#include "IniReader.h"

eSettingsManager* SettingsMgr = new eSettingsManager;

void eSettingsManager::Init()
{
	CIniReader ini("");
	CIniReader user("fablemenu_user.ini");


	iMenuOpenKey = ini.ReadInteger("Settings", "iMenuOpenKey", VK_OEM_3);
	iOverwriteConstantFPS = ini.ReadInteger("Settings", "iOverwriteConstantFPS", 15);
	bSlowMotionEffectsEverything = ini.ReadBoolean("Settings", "bSlowMotionEveywhere", false);
	bUseBuiltInWindowedMode = ini.ReadBoolean("Settings", "bUseBuiltInWindowedMode", false);
	iDefaultX = ini.ReadInteger("Settings", "iDefaultXRes", 1024);
	iDefaultY = ini.ReadInteger("Settings", "iDefaultYRes", 768);

	iFreeCameraKeyForward = user.ReadInteger("Settings", "iFreeCameraKeyForward", 0xFF);
	if (iFreeCameraKeyForward == 0xFF)
		iFreeCameraKeyForward = ini.ReadInteger("Settings", "iFreeCameraKeyForward", 0);

	iFreeCameraKeyBack = user.ReadInteger("Settings", "iFreeCameraKeyBack", 0xFF);
	if (iFreeCameraKeyBack == 0xFF)
		iFreeCameraKeyBack = ini.ReadInteger("Settings", "iFreeCameraKeyBack", 0);


	iFreeCameraKeyLeft = user.ReadInteger("Settings", "iFreeCameraKeyLeft ", 0xFF);
	if (iFreeCameraKeyLeft == 0xFF)
		iFreeCameraKeyLeft = ini.ReadInteger("Settings", "iFreeCameraKeyLeft", 0);

	iFreeCameraKeyRight = user.ReadInteger("Settings", "iFreeCameraKeyRight", 0xFF);
	if (iFreeCameraKeyRight == 0xFF)
		iFreeCameraKeyRight = ini.ReadInteger("Settings", "iFreeCameraKeyRight", 0);

	iFreeCameraKeyUp = user.ReadInteger("Settings", "iFreeCameraKeyUp", 0xFF);
	if (iFreeCameraKeyUp == 0xFF)
		iFreeCameraKeyUp = ini.ReadInteger("Settings", "iFreeCameraKeyUp", 0);

	iFreeCameraKeyDown = user.ReadInteger("Settings", "iFreeCameraKeyDown", 0xFF);
	if (iFreeCameraKeyDown == 0xFF)
		iFreeCameraKeyDown = ini.ReadInteger("Settings", "iFreeCameraKeyDown", 0);

	iHeroJumpKey = user.ReadInteger("Settings", "iHeroJumpKey", 0xFF);
	if (iHeroJumpKey == 0xFF)
		iHeroJumpKey = ini.ReadInteger("Settings", "iHeroJumpKey", 0);

	fMenuScale = user.ReadFloat("MenuSettings", "fMenuScale", 1.0f);

	if (fMenuScale < 1.0f)
		fMenuScale = 1.0f;


	mouse.sens = user.ReadFloat("Mouse", "Sensitivity", 2.0f);
	mouse.invert_y = user.ReadBoolean("Mouse", "InvertY", true);
	mouse.invert_x = user.ReadBoolean("Mouse", "InvertX", false);

}

void eSettingsManager::SaveSettings()
{
	CIniReader ini("");
	CIniReader user("fablemenu_user.ini");

	user.WriteFloat("MenuSettings", "fMenuScale", fMenuScale);
	user.WriteInteger("Settings", "iFreeCameraKeyForward", iFreeCameraKeyForward);
	user.WriteInteger("Settings", "iFreeCameraKeyBack", iFreeCameraKeyBack);
	user.WriteInteger("Settings", "iFreeCameraKeyLeft", iFreeCameraKeyLeft);
	user.WriteInteger("Settings", "iFreeCameraKeyRight", iFreeCameraKeyRight);
	user.WriteInteger("Settings", "iFreeCameraKeyUp", iFreeCameraKeyUp);
	user.WriteInteger("Settings", "iFreeCameraKeyDown", iFreeCameraKeyDown);
	user.WriteInteger("Settings", "iHeroJumpKey", iHeroJumpKey);
	user.WriteFloat("Mouse", "Sensitivity", mouse.sens);
	user.WriteBoolean("Mouse", "InvertY", mouse.invert_y);
	user.WriteBoolean("Mouse", "InvertX", mouse.invert_x);

	ini.WriteBoolean("Settings", "bSlowMotionEveywhere", bSlowMotionEffectsEverything);
	ini.WriteBoolean("Settings", "bUseBuiltInWindowedMode", bUseBuiltInWindowedMode);


}

void eSettingsManager::ResetKeys()
{
	iMenuOpenKey = VK_OEM_3;
	iFreeCameraKeyForward = 104;
	iFreeCameraKeyBack = 98;
	iFreeCameraKeyLeft = 100;
	iFreeCameraKeyRight = 102;
	iFreeCameraKeyUp = 103;
	iFreeCameraKeyDown = 97;
}
