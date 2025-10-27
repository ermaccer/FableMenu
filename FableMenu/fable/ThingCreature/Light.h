#pragma once
#include "../FCore.h"

class CTCLight {
public:
    char pad[0x1C];
    bool m_bActive;
    void SetOverridden(bool overriden);
    void SetColour(CRGBAColour* colour);
    void SetInnerRadius(float inner_radius);
    void SetOuterRadius(float outer_radius);
    void SetFlicker(unsigned char flicker);
    void SetActive(bool active);
};