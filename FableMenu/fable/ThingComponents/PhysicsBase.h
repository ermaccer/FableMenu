#pragma once
#include "Base.h"
#include "../FCore.h"

class CTCPhysicsStandard : public CTCBase {
public:
	CVector* GetPosition();
	CVector* GetVelocity();
	RHSet* GetRHSet();
	void SetPosition(CVector* position);

	bool IsCollisionEnabled();
	bool IsGravityEnabled();
	bool IsPhysicsEnabled();

	void EnablePhysics(bool enable);
	void EnableGravity(bool enable);
};