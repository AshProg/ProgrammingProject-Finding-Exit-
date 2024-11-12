#pragma once
#include "Entity.h"
#include "Player.h"

class Doctor : public Entity
{
private:
	Player* player;
	string fAnswer;
	bool fHaveTalked;

public:
	Doctor(Player* play) { fHaveTalked = false, player = play; }
	~Doctor();

	string first_Dialogue();
};