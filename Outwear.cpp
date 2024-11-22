#include "Outwear.h"

Outwear::Outwear()
{
	fSanityAdd = 0;
}

Outwear::Outwear(string name, int sanityAdd) : Objects("Increase you sanity by  substantial amount", name)
{
	fSanityAdd = sanityAdd;
}

int Outwear::get_SanityAddition()
{
	return fSanityAdd;
}