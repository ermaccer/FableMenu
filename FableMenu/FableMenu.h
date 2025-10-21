#pragma once
#include "Fable.h"


#define FABLEMENU_VERSION "1.0"


enum eMenuSubMenus {
	SM_Settings,
	SM_Creature_List,
	SM_Object_List,
	SM_Particle_List,
	SM_Total
};

enum eFreeCameraType {
	FREE_CAMERA_ORIGINAL,
	FREE_CAMERA_CUSTOM,
};

enum EMovementType {
	DEFAULT_MOVEMENT = -1,
	WALK_MOVEMENT = 0x2,
	RUN_MOVEMENT = 0x3,
	JOG_MOVEMENT = 0x4,
};

class FableMenu {
public:
	bool	 m_bIsActive = false;
	bool	 m_bSubmenuActive[SM_Total] = {};
	bool     m_bPressingKey = false;
	bool	 m_bIsFocused = true;

	bool	 freezeCam = false;
	bool	 m_bFrozeControls = false;
	bool	 m_bGodMode = false;
	bool	 m_bInfiniteWill = false;
	bool	 m_bMouseControl = false;
	bool     m_bForceLoadRegion = false;

	bool	 m_bNoBodyGuardsLimit = false;

	char szFactionName[128] = {};

	int		m_nFreeCameraMode = FREE_CAMERA_CUSTOM;


	int* m_pCurrentVarToChange = nullptr;

	float  m_fFreeCamSpeed = 300.0f;

	CVector camPos = {};
	CVector headPos = {};

	void Init();
	void Draw();
	void Process();

	void DrawHeroTab();
	void DrawPlayerTab();
	void DrawCreaturesTab();
	void DrawAppearanceCollapse(CThing* creature);
	void DrawActionsCollapse(CThing* creature);
	void DrawObjectData(const char* objectName, CThing* creature, bool* isOpen);
	void DrawObjectsTab();
	void DrawCameraTab();
	void DrawWorldTab();
	void DrawQuestTab();
	void DrawMiscTab();

	void DrawCreatureData(const char* creatureName, CThing* creature, bool* isOpen);
	void TakeActionItem(CThing* creature, char* objectName);
	void DrawPhysicsCollapse(CThing* creature);

	void DrawSettings();
	void DrawCreatureList();
	void DrawObjectList();
	void DrawParticleList();

	void DrawKeyBind(char* name, int* var);
	void KeyBind(int* var, char* bindName, char* name);

	void ChangeMovementTypePatch(EMovementType moveType);

	static std::vector<CThing*> m_createdParticles;
	static std::vector<CThing*> m_attachedCameraParticles;
	static bool m_bCustomCameraPos;
	static bool ms_bFreeCam;
	static bool ms_bDisableHUD;
	static bool m_bCustomCameraFOV;
	static bool ms_bChangeTime;
	static float m_fTime;
};

extern FableMenu* TheMenu;
void HookMainGameComponent();
void HookWorldUpdate();
bool InGame();

float GetDeltaTime();
bool IsWindowFocused();
