#include "Hero.h"
#include "../../core.h"

void CTCHero::SetTitle(int title_def_index)
{
	CallMethod<0x6CA400, CTCHero*, int>(this, title_def_index);
}
