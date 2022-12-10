#pragma once
#include "FCore.h"

enum EMovementType
{
	MovementType_Walking = 3
};


class CActionBase {
public:

};

class CActionMoveTo : public CActionBase {
public:
	char data[80];

	CActionMoveTo(CVector* pos, EMovementType movType, float proximity, bool faceMovement, bool avoidDynamicObstacles);
};