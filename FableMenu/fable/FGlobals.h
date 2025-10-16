#pragma once
#include "../Fable.h"

class FGlobals
{
public:
	static bool* GDoNotCallStartAutoSaveProgress;
	static bool* GDisplaySavingGameState;
	static bool* GUsePassiveAggressiveMode;
	static bool* GUseRubbishMovementMethod;
	static CVector* GOverridePlayerStartPos;
	static bool* GOverridePlayerStartPosFromConsole;
};

struct NGlobalConsole
{
	static bool* EnableHeroJump;
	static bool* EnableHeroSprint;
	static bool* EnableUpdateAI;
	static bool* EnableUpdateObjects;
	static bool* EnableParticles;
	static bool* EnableHeroThingCollision;
	static bool* HeroGodMode; 
	static bool* EnemyGodMode; 
};
