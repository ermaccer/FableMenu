#include "ScriptInterface.h"
#include "../core.h"

void CGameScriptInterface::Error(CCharString* assrt, CCharString* msg, CCharString* file, const CWideString* line)
{
    CallMethod<0x88DE00, CGameScriptInterface*, CCharString*, CCharString*, CCharString*, const CWideString*>(this, assrt, msg, file, line);
}

int CGameScriptInterface::RegisterTimer()
{
    return CallMethodAndReturn<int, 0x6E79E0, CGameScriptInterface*>(this);
}

void CGameScriptInterface::DeregisterTimer(int timer_index)
{
    CallMethod<0x6E7690, CGameScriptInterface*, int>(this, timer_index);
}

void CGameScriptInterface::SetTimer(int timer_index, int seconds)
{
    CallMethod<0x6E76E0, CGameScriptInterface*, int, int>(this, timer_index, seconds);
}

int CGameScriptInterface::GetTimer(int timer_index)
{
    return CallMethodAndReturn<int, 0x6E7710, CGameScriptInterface*, int>(this, timer_index);
}

void CGameScriptInterface::SetCreatureCreationDelayFrames(int frames)
{
    CallMethod<0x6E7D30, CGameScriptInterface*, int>(this, frames);
}

void CGameScriptInterface::ResetCreatureCreationDelayFrames()
{
    CallMethod<0x6E7D40, CGameScriptInterface*>(this);
}

void CGameScriptInterface::ShowOnScreenMessage(const C2DVector* screen_pos, CCharString* message, const CRGBAColour colour, const CCharString* font_name)
{
    CallMethod<0x892810, CGameScriptInterface*, const C2DVector*, CCharString*, const CRGBAColour, const CCharString*>(this, screen_pos, message, colour, font_name);
}

void CGameScriptInterface::ShowOnScreenMessage(CCharString* message, CCharString* button_1_response, CCharString* button_2_response, float display_time)
{
    CallMethod<0x8927B0, CGameScriptInterface*, CCharString*, CCharString*, CCharString*, float>(this, message, button_1_response, button_2_response, display_time);
}

void CGameScriptInterface::ShowOnScreenMessage(CCharString* message, float display_time)
{
    CallMethod<0x892780, CGameScriptInterface*, CCharString*, float>(this, message, display_time);
}

void CGameScriptInterface::AddScreenTitleMessage(CCharString* message, float display_time, CTCRegionDisplay* info_display = 0)
{
    CallMethod<0x89E4C0, CGameScriptInterface*, CCharString*, float, CTCRegionDisplay*>(this, message, display_time, info_display);
}

void CGameScriptInterface::GiveHeroYesNoQuestion(CCharString* message, CCharString* button_1_response, CCharString* button_2_response, CCharString* button_3_response, bool wait_before_asking)
{
    CallMethod<0x89E540, CGameScriptInterface*, CCharString*, CCharString*, CCharString*, CCharString*, bool>(this, message, button_1_response, button_2_response, button_3_response, wait_before_asking);
}

void CGameScriptInterface::DisplayGameInfo(CCharString* text_tag)
{
    CallMethod<0x8929D0, CGameScriptInterface*, CCharString*>(this, text_tag);
}

bool CGameScriptInterface::IsSafeToDisplayGameInfo()
{
    return CallMethodAndReturn<bool, 0x892B30, CGameScriptInterface*>(this);
}

void CGameScriptInterface::SheatheHeroWeapons()
{
    CallMethod<0x8916A0, CGameScriptInterface*>(this);
}

void CGameScriptInterface::RemoveAllHeroWeapons()
{
    CallMethod<0x898600, CGameScriptInterface*>(this);
}

void CGameScriptInterface::ConfiscateAllHeroItems()
{
    CallMethod<0x8986D0, CGameScriptInterface*>(this);
}

void CGameScriptInterface::ConfiscateAllHeroWeapons()
{
    CallMethod<0x8987E0, CGameScriptInterface*>(this);
}

void CGameScriptInterface::ConfiscateItemsOfTypeFromHero(CCharString* item_name)
{
    CallMethod<0x898840, CGameScriptInterface*, CCharString*>(this, item_name);
}

void CGameScriptInterface::ReturnAllConfiscatedItemsToHero()
{
    CallMethod<0x898940, CGameScriptInterface*>(this);
}

bool CGameScriptInterface::IsHeroOnQuest()
{
    return CallMethodAndReturn<bool, 0x891870, CGameScriptInterface*>(this);
}

void CGameScriptInterface::SetGuildMasterMessages(bool state)
{
    CallMethod<0x88E200, CGameScriptInterface*, bool>(this, state);
}

void CGameScriptInterface::RemoveAllAvailableQuestCardsFromGuild()
{
    CallMethod<0x891510, CGameScriptInterface*>(this);
}

void CGameScriptInterface::RemoveAllQuestInfoElements()
{
    CallMethod<0x891C30, CGameScriptInterface*>(this);
}

void CGameScriptInterface::DisplayTime(bool display)
{
    CallMethod<0x88E210, CGameScriptInterface*, bool>(this, display);
}

void CGameScriptInterface::DisplayMoneyBag(bool display)
{
    CallMethod<0x891C40, CGameScriptInterface*, bool>(this, display);
}

void CGameScriptInterface::DisplayMiniGameInfo(bool display, EMiniGameType type)
{
    CallMethod<0x891C60, CGameScriptInterface*, bool, EMiniGameType>(this, display, type);
}

void CGameScriptInterface::Pause(float seconds)
{
    CallMethod<0x88E4F0, CGameScriptInterface*, float>(this, seconds);
}

bool CGameScriptInterface::IsInCutscene()
{
    return CallMethodAndReturn<bool, 0x892270, CGameScriptInterface*>(this);
}

void CGameScriptInterface::SetCutsceneSkippable(bool state)
{
    CallMethod<0x892280, CGameScriptInterface*, bool>(this, state);
}

bool CGameScriptInterface::FadeScreenOut(float fade_in, float fade_out, CRGBAColour to_colour)
{
    return CallMethodAndReturn<bool, 0x890820, CGameScriptInterface*, float, float, CRGBAColour>(this, fade_in, fade_out, to_colour);
}

void CGameScriptInterface::FadeScreenIn()
{
    CallMethod<0x88E4C0, CGameScriptInterface*>(this);
}

void CGameScriptInterface::FastForwardTimeTo(float time, float seconds_to_take)
{
    CallMethod<0x88FE90, CGameScriptInterface*, float, float>(this, time, seconds_to_take);
}

void CGameScriptInterface::EnableDangerMusic(bool enable)
{
    CallMethod<0x891320, CGameScriptInterface*, bool>(this, enable);
}

bool CGameScriptInterface::IsDangerMusicEnabled()
{
    return CallMethodAndReturn<bool, 0x891330, CGameScriptInterface*>(this);
}

void CGameScriptInterface::SetSaveGameMarkerPos(const CVector* pos)
{
    CallMethod<0x88F960, CGameScriptInterface*, const CVector*>(this, pos);
}

void CGameScriptInterface::ResetToFrontEnd()
{
    CallMethod<0x88F970, CGameScriptInterface*>(this);
}

void CGameScriptInterface::CameraCircleAroundPos(const CVector* spos, const CVector* dolly, float time_for_360)
{
    CallMethod<0x892C20, CGameScriptInterface*, const CVector*, const CVector*, float>(this, spos, dolly, time_for_360);
}

void CGameScriptInterface::CameraMoveToPosAndLookAtPos(const CVector* from_pos, const CVector* to_pos, float no_seconds_movement)
{
    CallMethod<0x892410, CGameScriptInterface*, const CVector*, const CVector*, float>(this, from_pos, to_pos, no_seconds_movement);
}

void CGameScriptInterface::CameraMoveBetweenLookingAt(const CVector* start_pos, const CVector* end_pos, const CVector* look_at_pos, float num_secs, float fov)
{
    CallMethod<0x892530, CGameScriptInterface*, const CVector*, const CVector*, const CVector*, float, float>(this, start_pos, end_pos, look_at_pos, num_secs, fov);
}

bool CGameScriptInterface::IsCameraInScriptedMode()
{
    return CallMethodAndReturn<bool, 0x88ECC0, CGameScriptInterface*>(this);
}

bool CGameScriptInterface::IsCameraPosOnScreen(const CVector* pos)
{
    return CallMethodAndReturn<bool, 0x6E7300, CGameScriptInterface*, const CVector*>(this, pos);
}

void CGameScriptInterface::CameraEarthquakeIntensityAtPos(const CVector* pos, float intensity, float duration)
{
    CallMethod<0x88ED20, CGameScriptInterface*, const CVector*, float, float>(this, pos, intensity, duration);
}

void CGameScriptInterface::CameraShake(float intensity, float duration)
{
    CallMethod<0x88ECE0, CGameScriptInterface*, float, float>(this, intensity, duration);
}