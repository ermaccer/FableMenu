#pragma once
#include <list>
class CThing;

class CTCFollowed {
public:
	char pad[0x18];
	std::list<CThing*>* aiFollowers;
	CTCFollowed* Alloc(CThing* thing);
	void AddFollower(CThing* follower,bool is_ai_follower);
	void RemoveFollower(CThing* follower);
	void AddEmoteIcon(CThing* thing);
	void RemoveEmoteIcon(CThing* thing);
};