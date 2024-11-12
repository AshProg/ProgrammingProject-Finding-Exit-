#pragma once
#include "Entity.h"
#include "Inventory.h"
#include "InventoryIterator.h"
#include <string>
#include <iostream>
using namespace std;

class Player : public Entity
{
private:
	int fSanity = 100;
	Inventory* fInv;
	int fInvAmount = 1;

public:
	typedef InventoryIterator Iterator;

	Player(string name, bool liveordeath, Inventory* inv);
	~Player();

	void EntersRoom();

	void ReplenishSanity();
	void UseSalt();
	void UsePills();
	int get_Sanity();
	void PickUpObject(Objects* obj);
	int InvAmount();
	Iterator get_Iterator();
	Inventory* get_Inv();
	void RemoveObject();
	void set_Name(string name)
	{
		fName = name;
	}

	void set_Sanity(int sanity)
	{
		fSanity += sanity;
		if (fSanity < 0)
		{
			fSanity = 0;
		}
	}

};