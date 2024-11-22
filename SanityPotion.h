#pragma once
#include "Objects.h"

class SanityPotion : public Objects
{
private:
	int fReplenishAmount;

public:
	SanityPotion(int replenishAmount);

	int get_ReplenishAmount();
};