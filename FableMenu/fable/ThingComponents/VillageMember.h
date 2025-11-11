#pragma once

class CThing;
class CTCVillage;

class CTCVillageMember {
public:
	CTCVillage* GetPVillage();
	bool IsAttachedToVillage();
};