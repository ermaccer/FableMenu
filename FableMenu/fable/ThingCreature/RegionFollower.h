
class CThing;

class CTCRegionFollower {
public:
	CTCRegionFollower* Alloc(CThing* thing);
	void AddFollower(CThing* thing);
	void RemoveFollower(CThing* thing);
};