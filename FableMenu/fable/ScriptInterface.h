#pragma once
#include "Thing.h"

class C2DVector
{
public:
	float X, Y;
	C2DVector(void) {}
	C2DVector(float a, float b)
	{
		X = a;
		Y = b;
	}
};

enum EMiniGameType
{
	MINIGAME_NONE,
	MINIGAME_FISHING,
	MINIGAME_DIGGING,
    MINIGAME_PICKPOCKET,
	MINIGAME_PICKLOCK,
	MINIGAME_STEAL,
	MINIGAME_TROPHY,
	MINIGAME_ORACLE
};

class CGameScriptInterface {
public:
	void Error(CCharString* assrt, CCharString* msg, CCharString* file, const CWideString* line);
	int RegisterTimer();
	void DeregisterTimer(int timer_index);
	void SetTimer(int timer_index, int seconds);
	int GetTimer(int timer_index);
	void SetCreatureCreationDelayFrames(int frames);
	void ResetCreatureCreationDelayFrames();
	void ShowOnScreenMessage(const C2DVector* screen_pos, CCharString* message, const CRGBAColour colour, const CCharString* font_name);
	void ShowOnScreenMessage(CCharString* message, CCharString* button_1_response, CCharString* button_2_response, float display_time);
	void ShowOnScreenMessage(CCharString* message, float display_time);
	void AddScreenTitleMessage(CCharString* message, float display_time, CTCRegionDisplay* info_display);
	void GiveHeroYesNoQuestion(CCharString* message, CCharString* button_1_response, CCharString* button_2_response, CCharString* button_3_response, bool wait_before_asking);
	void DisplayGameInfo(CCharString* text_tag);
	bool IsSafeToDisplayGameInfo();
	void SheatheHeroWeapons();
	void RemoveAllHeroWeapons();
	void ConfiscateAllHeroItems();
	void ConfiscateAllHeroWeapons();
	void ConfiscateItemsOfTypeFromHero(CCharString* item_name);
	void ReturnAllConfiscatedItemsToHero();
	bool IsHeroOnQuest();
	void SetGuildMasterMessages(bool state);
	void RemoveAllAvailableQuestCardsFromGuild();
	void RemoveAllQuestInfoElements();
	void DisplayTime(bool display);
	void DisplayMoneyBag(bool display);
	void DisplayMiniGameInfo(bool display, EMiniGameType type);
	void Pause(float seconds);
	bool IsInCutscene();
	void SetCutsceneSkippable(bool state);
	bool FadeScreenOut(float fade_in, float fade_out, CRGBAColour to_colour);
	void FadeScreenIn();
	void FastForwardTimeTo(float time, float seconds_to_take);
	void EnableDangerMusic(bool enable);
	bool IsDangerMusicEnabled();
	void SetSaveGameMarkerPos(const CVector* pos);
	void ResetToFrontEnd();
	void CameraCircleAroundPos(const CVector* spos, const CVector* dolly, float time_for_360);
	void CameraMoveToPosAndLookAtPos(const CVector* from_pos, const CVector* to_pos, float no_seconds_movement);
	void CameraMoveBetweenLookingAt(const CVector* start_pos, const CVector* end_pos, const CVector* look_at_pos, float num_secs, float fov);
	bool IsCameraInScriptedMode();
	bool IsCameraPosOnScreen(const CVector* pos);
	void CameraEarthquakeIntensityAtPos(const CVector* pos, float intensity, float duration);
	void CameraShake(float intensity, float duration);
};