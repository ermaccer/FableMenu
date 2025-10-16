#include "ActionPlayAnimation.h"
#include "../../core.h"

CActionPlayAnimation::CActionPlayAnimation(CActionBase* CActionPlayAnimation, CCharString* AnimName, bool stay_on_last_frame, bool looping, int num_loops, bool use_movement, int priority, bool add_as_queued_action, bool wait_for_anim_to_finish, bool use_physics, bool anim_may_need_camera_position_updated_in_speak_and_wait, bool allow_looking)
{
	CallMethod<0x9034F0, CActionBase*, CCharString*, bool, bool, int, bool, int, bool, bool, bool, bool, bool>(CActionPlayAnimation, AnimName, stay_on_last_frame, looping, num_loops, use_movement, priority, add_as_queued_action, wait_for_anim_to_finish, use_physics, anim_may_need_camera_position_updated_in_speak_and_wait, allow_looking);
}
