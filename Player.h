#pragma once
#include "Inventory.h"
#include "InventoryIterator.h"
#include "OutwearInv.h"
#include <string>
#include <iostream>
using namespace std;

// Player class that represents a player in the game, including their inventory and sanity level
class Player
{
private:
    string fName;          // Name of the player
    int fSanity = 100;     // Player's current sanity level, initialized to 100
    int newSanity = 100;   // Temporary variable for sanity changes
    Inventory* fInv;       // Pointer to the player's inventory
    OutwearInv* fOutwear;  // Pointer to the player's Outwear inventory

public:
    typedef InventoryIterator Iterator;  // Type definition for the inventory iterator

    // Constructor that initializes the player with a name, inventory, and outwear inventory
    Player(string name, Inventory* inv, OutwearInv* OInv);

    // Destructor to clean up resources when the player object is destroyed
    ~Player();

    // Setter for setting the player's sanity to a specific value
    void set_Sanity(int sanity);

    // Getter for getting the current sanity of the player
    int get_Sanity();

    // Getter for getting the player's name
    string get_Name();

    // Setter for setting the player's name
    void set_Name(string name);

    // Inventory-related functions:

    // Replenishes the player's sanity by using items (like sanity potions)
    bool ReplenishSanity();

    // Uses salt from the inventory (assumed to be a method for applying salt-related effects)
    bool UseSalt();

    // Adds an object to the player's inventory (e.g., items the player picks up)
    void PickUpObject(Objects* obj);

    // Retrieves an iterator to iterate over the player's inventory
    Iterator get_Iterator();

    // Getter for accessing the player's inventory
    Inventory* get_Inv();

    // Removes an object from the player's inventory
    void RemoveObject();

    // Outwear-related functions:

    // Uses an Outwear item (e.g., equips clothing or protection from the inventory)
    void UseOutwear(Outwear* out);

    // Removes an Outwear item from the player's outwear inventory
    void RemoveOutwear();

    // Getter for retrieving the current Outwear item the player is using
    Outwear* get_Outwear();
};
