#pragma once

namespace HUD {
	bool __fastcall Display(int ptr);
}


class CHUD {
public:
	char pad[0x290];
	bool m_bDisplay;
	bool m_unk;
	bool m_bShowTimer;
	bool m_bShowMoney;
	bool m_unk2;
	float m_fTransparency;
};


CHUD* GetHud();