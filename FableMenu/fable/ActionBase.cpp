#include "ActionBase.h"
#include "..\core.h"

CActionMoveTo::CActionMoveTo(CVector* pos, EMovementType movType, float proximity, bool faceMovement, bool avoidDynamicObstacles)
{
	CallMethod<0x7E71D0, CActionMoveTo*, CVector*, EMovementType, float, bool, bool>(this, pos, movType, proximity, faceMovement, avoidDynamicObstacles);
}
