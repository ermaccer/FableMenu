#include "Light.h"
#include "../../core.h"

void CTCLight::SetOverridden(bool overriden)
{
	CallMethod<0x640DF0, CTCLight*, bool>(this, overriden);
}

void CTCLight::SetColour(CRGBAColour* colour)
{
	CallMethod<0x640BB0, CTCLight*, CRGBAColour*>(this, colour);
}

void CTCLight::SetInnerRadius(float inner_radius)
{
	CallMethod<0x640C40, CTCLight*, float>(this, inner_radius);
}

void CTCLight::SetOuterRadius(float outer_radius)
{
	CallMethod<0x640C70, CTCLight*, float>(this, outer_radius);
}

void CTCLight::SetFlicker(unsigned char flicker)
{
	CallMethod<0x682160, CTCLight*, unsigned char>(this, flicker);
}

void CTCLight::SetActive(bool active)
{
	CallMethod<0x6412B0, CTCLight*, bool>(this, active);
}