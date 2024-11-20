#include "Player.h"

Player::Player(string name, bool liveordeath, Inventory* inv) : Entity(name, liveordeath)
{
    fInv = inv;
}

bool Player::ReplenishSanity()
{
    bool potionUsed = false;

    // Use InventoryIterator for traversal
    InventoryIterator it = get_Iterator();

    while (it != it.end())
    {
        SanityPotion* potion = dynamic_cast<SanityPotion*>(it.getCurrent()->get_Object());
        if (potion != nullptr)
        {
            // Replenish sanity and handle overflow
            fSanity += potion->get_ReplenishAmount();
            if (fSanity > 100)
            {
                fSanity = 100;
            }
            cout << "Sanity replenished by " << potion->get_ReplenishAmount() << " points!" << endl;

            // Remove the used potion and update inventory count
            Inventory* toDelete = it.getCurrent();
            ++it; // Advance the iterator before deletion
            toDelete->Remove();
            fInvAmount -= 1;

            potionUsed = true;
            return true;
        }
        else
        {
            ++it; // Move to the next item
        }
    }

    if (!potionUsed)
    {
        cout << "Out of SANITY POTIONS!!" << endl;
    }
    return potionUsed;
}

bool Player::UseSalt()
{
    bool saltUsed = false;

    // Use InventoryIterator for traversal
    InventoryIterator it = get_Iterator();

    while (it != it.end())
    {
        PurifiedSalt* salt = dynamic_cast<PurifiedSalt*>(it.getCurrent()->get_Object());
        if (salt != nullptr)
        {
            cout << "You used Purified Salt on the ghost! It will be stunned for a while!" << endl;

            // Remove the used salt and update inventory count
            Inventory* toDelete = it.getCurrent();
            ++it; // Advance the iterator before deletion
            toDelete->Remove();
            fInvAmount -= 1;

            saltUsed = true;
            return true;
        }
        else
        {
            ++it; // Move to the next item
        }
    }

    if (!saltUsed)
    {
        cout << "Out of PURIFIED SALT!!" << endl;
    }
    return saltUsed;
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

void Player::RemoveObject()
{
    // Use InventoryIterator for traversal
    InventoryIterator it = get_Iterator();

    while (it != it.end())
    {
        Inventory* toDelete = it.getCurrent();
        ++it; // Advance the iterator before deletion
        toDelete->Remove();
    }

    // Reset inventory-related variables
    fInvAmount = 0;
    cout << "Inventory cleared!" << endl;
}

Player::~Player()
{
    InventoryIterator it = get_Iterator();
    while (it != it.end())
    {
        Inventory* toDelete = it.getCurrent();
        ++it;
        toDelete->Remove();
    }
}
