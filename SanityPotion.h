#pragma once
#include "Objects.h"

class SanityPotion : public Objects
{
private:
	int fReplenishAmount;
	
public:
	SanityPotion(int replenishAmount) : Objects("Increase Sanity by 50", "Sanity Potion") { fReplenishAmount = replenishAmount; }

	int get_ReplenishAmount() { return fReplenishAmount; }
};