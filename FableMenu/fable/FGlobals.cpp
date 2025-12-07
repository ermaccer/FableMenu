#include "FGlobals.h"
#include "../core.h"

bool& FGlobals::GDoNotCallStartAutoSaveProgress = *(bool*)0x13B89D1;

bool& FGlobals::GDisplaySavingGameState = *(bool*)0x13B89C1;

bool& FGlobals::GUsePassiveAggressiveMode = *(bool*)0x13B85F3;

bool& FGlobals::GUseRubbishMovementMethod = *(bool*)0x13756EA;

bool& FGlobals::GOverridePlayerStartPosFromConsole = *(bool*)(0x13B8647);

CVector* FGlobals::GOverridePlayerStartPos = (CVector*)(0x13B8650);