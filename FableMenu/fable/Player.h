#pragma once
#include "Thing.h"
class CPlayer {
public:
	void SetMode(int id, bool unk);
	void ClearMode(int id);

	CThing* GetCharacterThing();

	void DisableInput();
	void EnableInput();
};