#pragma once
#include "Objects.h"

class Outwear : public Objects
{
private:
	int fSanityAdd;

public:
	Outwear()
	{
		fSanityAdd = 0;
	}

	Outwear(string name, int sanityAdd) : Objects("Increase you sanity by  substantial amount", name)
	{
		fSanityAdd = sanityAdd;
	}
	
	~Outwear();

	int get_SanityAddition()
	{
		return fSanityAdd;
	}
};