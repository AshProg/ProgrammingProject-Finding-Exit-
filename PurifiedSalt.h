#pragma once
#include "Objects.h"

class PurifiedSalt : public Objects
{
private:

public:
	PurifiedSalt(int amount) : Objects("Stunned the ghost for a while", "Purified Salt", amount)
	{}
};