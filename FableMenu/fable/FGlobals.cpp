#include "FGlobals.h"

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