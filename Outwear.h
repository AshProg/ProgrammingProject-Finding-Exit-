#pragma once
#include "Objects.h"

class Outwear : public Objects
{
private:
	int fSanityAdd;

public:
	Outwear();
	
	Outwear(string name, int sanityAdd);
	int get_SanityAddition();
};