#pragma once
#include "Entity.h"
#include "Inventory.h"
#include "InventoryIterator.h"
#include "OutwearInv.h"
#include <string>
#include <iostream>
using namespace std;

class Player : public Entity
{
private:
	int fSanity = 100;
	int newSanity = 100;
	Inventory* fInv;
	OutwearInv* fOutwear;
	int fInvAmount = 1;

public:
	typedef InventoryIterator Iterator;

	Player(string name, bool liveordeath, Inventory* inv);
	~Player();

	bool ReplenishSanity();
	bool UseSalt();
	int get_Sanity();
	void PickUpObject(Objects* obj);
	int InvAmount();
	Iterator get_Iterator();
	Inventory* get_Inv();
	void RemoveObject();

	void set_Sanity(int sanity)
	{
		fSanity += sanity;
		if (fSanity < 0)
		{
			fSanity = 0;
		}
		if (fSanity > newSanity)
		{
			fSanity = newSanity;
		}
	}

};