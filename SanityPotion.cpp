#include "SanityPotion.h"

SanityPotion::SanityPotion(int replenishAmount) : Objects("Increase Sanity by 50", "Sanity Potion") 
{ 
	fReplenishAmount = replenishAmount; 
}

int SanityPotion::get_ReplenishAmount()
{ 
	return fReplenishAmount; 
}