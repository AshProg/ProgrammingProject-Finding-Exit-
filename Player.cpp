#include "Player.h"

Player::Player(string name, bool liveordeath, Inventory* inv) : Entity(name, liveordeath) 
{
	fInv = inv;
}

void Player::ReplenishSanity()
{
    bool potionUsed = false;
    Inventory* holder = fInv;

    // Iterate through the inventory linked list
    while (holder != &(Inventory::NIL))
    {
        // Try to cast the current object to a SanityPotion
        SanityPotion* potion = dynamic_cast<SanityPotion*>(holder->get_Object());
        if (potion != nullptr)
        {
            // Replenish sanity by the potion's amount
            fSanity += potion->get_ReplenishAmount();
            if (fSanity > 100)
            {
                fSanity = 100;
            }
            cout << "Sanity replenished by " << potion->get_ReplenishAmount() << " points!" << endl;
            potionUsed = true;
            holder->Remove();
            fInvAmount -= 1;
            break;
        }
        else
        {
            holder = holder->get_Prev(); // Move to the next item in the inventory
        }
    }

    // If no potion was found
    if (!potionUsed)
    {
        cout << "Out of SANITY POTIONS!!" << endl;
    }
}

void Player::UseSalt()
{
    bool saltUsed = false;
    Inventory* holder = fInv;

    // Iterate through the inventory linked list
    while (holder != &(Inventory::NIL))
    {
        // Try to cast the current object to a SanityPotion
        PurifiedSalt* salt = dynamic_cast<PurifiedSalt*>(holder->get_Object());
        if (salt != nullptr)
        {
            cout << "You used Purified Salt on the ghost! It will be stunned for a while!" << endl;

            // Mark the potion as used
            saltUsed = true;
            holder->Remove();
            fInvAmount -= 1;
            break; // Exit the loop after using one potion
        }
        else
        {
            holder = holder->get_Prev(); // Move to the next item in the inventory
        }
    }

    // If no potion was found
    if (!saltUsed)
    {
        cout << "Out of PURIFIED SALT!!" << endl;
    }
}


int Player::get_Sanity()
{
	return fSanity;
}

void Player::PickUpObject(Objects* obj)
{
    fInvAmount += 1;
	fInv->Add(new Inventory(obj));
	cout << "Item Successfully added into inventory!\n" << endl;
}

Inventory* Player::get_Inv()
{
    return fInv;
}

int Player::InvAmount()
{
    return fInvAmount;
}

InventoryIterator Player::get_Iterator()
{
    return InventoryIterator(fInv);
}

Player::~Player()
{
    Iterator it = get_Iterator();
    while (it != it.end())
    {
        Inventory* toDelete = it.getCurrent();
        ++it;
        toDelete->Remove();
    }
}