#include "Player.h"

// Constructor that initializes the player with a name, inventory, and outwear inventory
Player::Player(string name, Inventory* inv, OutwearInv* OInv)
{
    fName = name;        // Set player name
    fInv = inv;          // Set player inventory
    fOutwear = OInv;     // Set player outwear inventory
}

// Replenishes sanity by using a SanityPotion from the inventory
bool Player::ReplenishSanity()
{
    bool potionUsed = false;

    // Use InventoryIterator to traverse through inventory
    InventoryIterator it = get_Iterator();

    while (it != it.end())  // Loop through inventory until the end is reached
    {
        // Try to cast current item to a SanityPotion
        SanityPotion* potion = dynamic_cast<SanityPotion*>(it.getCurrent()->get_Object());
        if (potion != nullptr)  // If it is a SanityPotion
        {
            // Replenish sanity and handle overflow
            set_Sanity(potion->get_ReplenishAmount());
            cout << "Sanity replenished by " << potion->get_ReplenishAmount() << " points!" << endl;

            // Remove the used potion and update inventory
            Inventory* toDelete = it.getCurrent();
            --it;  // Move iterator before deletion to avoid accessing invalid memory
            toDelete->Remove();  // Remove potion from inventory

            potionUsed = true;
            return true;
        }
        else
        {
            --it;  // Move to the next item if it's not a SanityPotion
        }
    }

    if (!potionUsed)
    {
        cout << "Out of SANITY POTIONS!!" << endl;  // If no potion found, print message
    }
    return potionUsed;
}

// Uses Purified Salt to stun the ghost
bool Player::UseSalt()
{
    bool saltUsed = false;

    // Use InventoryIterator to traverse through inventory
    InventoryIterator it = get_Iterator();

    while (it != it.end())  // Loop through inventory until the end is reached
    {
        // Try to cast current item to PurifiedSalt
        PurifiedSalt* salt = dynamic_cast<PurifiedSalt*>(it.getCurrent()->get_Object());
        if (salt != nullptr)  // If it is PurifiedSalt
        {
            cout << "You used Purified Salt on the ghost! It will be stunned for a while!" << endl;

            // Remove the used salt and update inventory
            Inventory* toDelete = it.getCurrent();
            --it;  // Move iterator before deletion to avoid accessing invalid memory
            toDelete->Remove();  // Remove salt from inventory

            saltUsed = true;
            return true;
        }
        else
        {
            --it;  // Move to the next item if it's not PurifiedSalt
        }
    }

    if (!saltUsed)
    {
        cout << "Out of PURIFIED SALT!!" << endl;  // If no salt found, print message
    }
    return saltUsed;
}

// Returns current sanity value
int Player::get_Sanity()
{
    return fSanity;
}

// Adds an object to the player's inventory
void Player::PickUpObject(Objects* obj)
{
    fInv->Add(new Inventory(obj));  // Add the object to the inventory
    cout << "Item Successfully added into inventory!\n" << endl;
}

// Returns a pointer to the player's inventory
Inventory* Player::get_Inv()
{
    return fInv;
}

// Returns an iterator for the player's inventory
InventoryIterator Player::get_Iterator()
{
    return InventoryIterator(fInv);  // Return an iterator for traversing the inventory
}

// Removes all objects from the player's inventory
void Player::RemoveObject()
{
    // Use InventoryIterator to traverse through inventory
    InventoryIterator it = get_Iterator();

    while (it != it.end())  // Loop through inventory until the end is reached
    {
        Inventory* toDelete = it.getCurrent();
        ++it;  // Move iterator before deletion to avoid accessing invalid memory
        toDelete->Remove();  // Remove the current object from inventory
    }

    cout << "Inventory cleared!" << endl;  // Print message after clearing inventory
}

// Sets the player's sanity, ensuring it stays within bounds (0 to max sanity)
void Player::set_Sanity(int sanity)
{
    fSanity += sanity;  // Add the given sanity amount to the current sanity
    if (fSanity < 0)  // If sanity falls below 0, set it to 0
    {
        fSanity = 0;
    }
    if (fSanity > newSanity)  // If sanity exceeds max allowed value, set it to max
    {
        fSanity = newSanity;
    }
}

// Sets the player's name
void Player::set_Name(string name)
{
    fName = name;
}

// Returns the player's name
string Player::get_Name() { return fName; }

// Adds outwear to the player's outwear inventory and adjusts sanity accordingly
void Player::UseOutwear(Outwear* out)
{
    fOutwear->Add(out);  // Add outwear to inventory
    newSanity = fOutwear->get_Current()->get_SanityAddition();  // Update sanity based on outwear's effect
    set_Sanity(newSanity);  // Set new sanity value
}

// Removes outwear from the player's outwear inventory
void Player::RemoveOutwear()
{
    fOutwear->Remove();  // Remove outwear from inventory
}

// Returns the current outwear item the player is using
Outwear* Player::get_Outwear()
{
    Outwear* temp = fOutwear->get_Current();  // Get current outwear from inventory
    return temp;
}

// Destructor that clears the player's inventory when the object is destroyed
Player::~Player()
{
    InventoryIterator it = get_Iterator();
    while (it != it.end())  // Loop through inventory until the end is reached
    {
        Inventory* toDelete = it.getCurrent();
        ++it;  // Move iterator before deletion to avoid accessing invalid memory
        toDelete->Remove();  // Remove the current object from inventory
    }
}
