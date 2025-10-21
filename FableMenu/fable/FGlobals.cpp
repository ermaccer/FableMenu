#include "FGlobals.h"
#include "../core.h"

bool* FGlobals::GDoNotCallStartAutoSaveProgress = (bool*)0x13B89D1;

bool* FGlobals::GDisplaySavingGameState = (bool*)0x13B89C1;

bool* FGlobals::GUsePassiveAggressiveMode = (bool*)0x13B85F3;

bool* FGlobals::GUseRubbishMovementMethod = (bool*)0x13756EA;

bool* FGlobals::GOverridePlayerStartPosFromConsole = (bool*)(0x13B8647);

CVector* FGlobals::GOverridePlayerStartPos = (CVector*)(0x13B8650);

bool* NGlobalConsole::EnableHeroJump = (bool*)0x13B86E5;

bool* NGlobalConsole::EnableHeroSprint = (bool*)0x13B86C5;

bool* NGlobalConsole::EnableUpdateAI = (bool*)0x1375756;

bool* NGlobalConsole::EnableUpdateObjects = (bool*)0x1375759;

bool* NGlobalConsole::EnableParticles = (bool*)0x1375754;

bool* NGlobalConsole::EnableHeroThingCollision = (bool*)0x13756E9;

bool* NGlobalConsole::HeroGodMode = (bool*)0x13B86C7;

bool* NGlobalConsole::EnemyGodMode = (bool*)0x13B86C8;

bool* NGlobalConsole::ForcePrimitiveFadeDistance = (bool*)0x13B86CA;

float* NGlobalConsole::PrimitiveFadeDistance = (float*)0x1375710;

bool* NGlobalConsole::GCombatStressTestDebug = (bool*)0x13B86D5;

float* NGlobalConsole::ConsoleOverrideMultiplier = (float*)0x13BAF18;

void NGlobalConsole::ConsoleTeleportToHSP(char* hsp)
{
	CCharString hsp_name(hsp);
	CWorld* world = CMainGameComponent::Get()->GetWorld();

	world->TeleportHeroToHSP(&hsp_name);
}

void NGlobalConsole::ConsoleReloadCurrentRegion()
{
	CWorldMap* worldMap = CThing::GetWorldMap();
	CallMethod<0x5025B0, CWorldMap*>(worldMap);
}

void NGlobalConsole::AutoSave()
{
	CMainGameComponent::Get()->GetWorld()->AutoSave(0);
}
