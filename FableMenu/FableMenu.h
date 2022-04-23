#pragma once

enum eMenuTab {
	TAB_PLAYER,
	TAB_CAMERA,
	TAB_WORLD,
	TAB_MISC
};

class FableMenu {
public:
	bool active = false;
	bool freezeCam = false;
	bool frozeControls = false;
	bool godMode = false;

	void Init();
	void Render();
	void Process();

	static bool ms_bFreezeCamera;
	static bool ms_bEnableFreeCamera;
	static bool ms_bDisableHUD;
	static bool ms_bChangeFOV;
	static bool ms_bChangeTime;
	static float m_fTime;
};

extern FableMenu* TheMenu;


void HookWorldUpdate();
bool InGame();