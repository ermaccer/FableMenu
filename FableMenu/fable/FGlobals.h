#pragma once
#include "../Fable.h"

class FGlobals {
public:
	static bool& GDoNotCallStartAutoSaveProgress;
	static bool& GDisplaySavingGameState;
	static bool& GUsePassiveAggressiveMode;
	static bool& GUseRubbishMovementMethod;
	static CVector* GOverridePlayerStartPos;
	static bool& GOverridePlayerStartPosFromConsole;
};

namespace NGlobalConsole {
	static bool& EnableHeroJump = *(bool*)0x13B86E5;
	static bool& EnableHeroSprint = *(bool*)0x13B86C5;
	static bool& EnableUpdateAI = *(bool*)0x1375756;
	static bool& EnableUpdateObjects = *(bool*)0x1375759;
	static bool& EnableParticles = *(bool*)0x1375754;
	static bool& EnableHeroThingCollision = *(bool*)0x13756E9;
	static bool& HeroGodMode = *(bool*)0x13B86C7;
	static bool& EnemyGodMode = *(bool*)0x13B86C8;
	static bool& ForcePrimitiveFadeDistance = *(bool*)0x13B86CA;
	static int&  PrimitiveFadeDistance = *(int*)0x1375710;
	static bool& GCombatStressTestDebug = *(bool*)0x13B86D5;
	static float& ConsoleOverrideMultiplier = *(float*)0x13BAF18;
	static bool& GEnableRegionLockingSaveSystem = *(bool*)0x1375741;
};
