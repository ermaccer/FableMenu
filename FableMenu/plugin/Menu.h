#pragma once
#include "..\Fable.h"
#include <vector>
#include "../helper/eKeyboardMan.h"

#define FABLEMENU_VERSION "0.6"
#define NUM_FACTIONS 30
#define NUM_BRAIN_NAMES 113
#define NUM_CREATURES 700
#define NUM_OBJECTS 2822
#define NUM_PARTICLES 1165
#define NUM_CREATURE_ANIMATIONS 231
#define NUM_BUILTIN_QUESTS 187
#define NUM_EXPRESSION_NAMES 38
#define NUM_PLAYER_MODE_NAMES 48
#define NUM_CREATURE_MODE_NAMES 96
#define NUM_CREATURE_WEAPONS 85
#define NUM_ATTACK_STYLE_NAMES 89
#define NUM_HOLY_SITES 95

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


extern const char* szFactions[NUM_FACTIONS];
extern const char* szBrainNames[NUM_BRAIN_NAMES];
extern const char* szCreatureList[NUM_CREATURES];
extern const char* szObjectsList[NUM_OBJECTS];
extern const char* szParticleList[NUM_PARTICLES];
extern const char* szCreatureAnimations[NUM_CREATURE_ANIMATIONS];
extern const char* szBuiltInQuests[NUM_BUILTIN_QUESTS];
extern const char* expressionNames[NUM_EXPRESSION_NAMES];
extern const char* szPlayerModeNames[NUM_PLAYER_MODE_NAMES];
extern const char* szCreatureModeNames[NUM_CREATURE_MODE_NAMES];
extern const char* szCreatureWeapons[NUM_CREATURE_WEAPONS];
extern const char* szAttackStyleNames[NUM_ATTACK_STYLE_NAMES];
extern const char* szHolySites[NUM_HOLY_SITES];

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

	FableMenu();

	void	 OnActivate();

	void	 Draw();
	void	 Process();

	void	 DrawHeroTab();
	void	 DrawPlayerTab();
	void	 DrawCreaturesTab();
	void	 DrawAppearanceCollapse(CThing* creature);
	void	 DrawActionsCollapse(CThing* creature);

	void	 DrawObjectData(const char* objectName, CThing* creature, bool* isOpen);
	void	 DrawObjectsTab();
	void	 DrawCameraTab();
	void	 DrawWorldTab();
	void	 DrawQuestTab();
	void	 DrawMiscTab();

	void	 DrawCreatureData(const char* creatureName, CThing* creature, bool* isOpen);
	void	 TakeActionItem(CThing* creature, char* objectName);
	void	 DrawPhysicsCollapse(CThing* creature);

	void	 DrawSettings();
	void	 DrawCreatureList();
	void	 DrawObjectList();
	void	 DrawParticleList();

	void	 DrawKeyBind(char* name, int* var);
	void	 KeyBind(int* var, char* bindName, char* name);
	void	 GameKeyBind(int* var, char* bindName, char* name, EGameAction action);

	void	 ChangeMovementTypePatch(EMovementType moveType);

	static std::vector<CThing*> m_createdParticles;
	static std::vector<CThing*> m_attachedCameraParticles;
	static bool m_bCustomCameraPos;
	static bool ms_bFreeCam;
	static bool ms_bDisableHUD;
	static bool m_bCustomCameraFOV;
	static bool ms_bChangeTime;
	static bool ms_bDisableCreateParticle;
	static float m_fTime;
};

extern FableMenu* TheMenu;
void HookMainGameComponent();
void HookWorldUpdate();
bool InGame();

bool IsWindowFocused();
char* GetUTF8String(wchar_t* name);
void CopyToClipboard(char* name);
