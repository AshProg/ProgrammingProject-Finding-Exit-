#include "Narrator.h"


Narrator::Narrator() : top(nullptr) {}

Narrator::Narrator(string msg, Player* player) : message(msg), next(nullptr), player(player) {}

Narrator::~Narrator()
{
    Node* currentNode = top;
    while (currentNode != nullptr)
    {
        Node* temp = currentNode;
        currentNode = currentNode->next;
        delete temp; // Delete the current node
    }
}

void Narrator::push(string msg)
{
    Node* newNode = new Node(msg, player);
    newNode->next = top;
    top = newNode;
}

void Narrator::pop()
{
    if (!isEmpty())
    {
        Node* temp = top;
        top = top->next;
        delete temp;
    }
}

string Narrator::peekThenPop()
{
    if (isEmpty())
    {
        return "Stack is empty.";
    }
    
    string message = top->message; // Get the top message
    pop();
    return message;
}

string Narrator::get_Next()
{
    if (top == nullptr)
    {
        return "End of stack reached.";
    }
    string message = top->message;
    top = top->next; // Move to the next node
    return message;
}

bool Narrator::isEmpty() const
{
    return top == nullptr;
}

void Narrator::Introduction()
{
    push("PRESS \"W\" TO WAKE UP!");
    push("----------------------------------------------");
    push("as fast as you can before they catch you!   ");
    push("You need to find the key to the entrance   ");
    push("by the residers in it.\" It says.            ");
    push("\"Get out of this house before you get eaten ");
    push("The sound says like this:                   ");
    push("There is a sound whispering in your ear.    ");
    push("When you look around, there is nothing to see.       ");
    push("You wanders around in the room");
    push("----------------------------------------------\n");
    push("------------------INTRODUCTION------------------\n");
}

void Narrator::Pause()
{
    push("[Q] QUIT");
    push("[M] MAIN MENU");
    push("[R] RESUME");
    push("GAME PAUSED! WHAT YOU WANT TO DO?");
}

void Narrator::AfterWakeUp()
{
    push("Do you want to go outside? (Yes or No)");
    push("You a saw a door to go outside.");
    push("That dream that reminds you to get out ASAP.");
    push("You just woke up from that dream on this crooked bed.");
}

void Narrator::Hall()
{
    push(">> Entrance");
    push(">> Room 2");
    push(">> Bathroom");
    push(">> Kitchen");
    push("What you would do now?");
    push("When you try to open it, it is locked. You need a Key!");
    push("You wander around and saw the entrance door.");
    push("First is the kitchen, second is the bathroom and third is another room.");
    push("Outside is the hall where you see there are 3 other rooms.");
}

void Narrator::SeeInventory()
{
    int fPotion = 0;
    int fSalt = 0;
    string fePotion, feSalt;
    Inventory* holder = player->get_Inv();

    while (holder != &(Inventory::NIL))
    {
        // Check if the item is a SanityPotion
        SanityPotion* potion = dynamic_cast<SanityPotion*>(holder->get_Object());
        if (potion != nullptr)
        {
            ++fPotion;
            fePotion = potion->get_ObjEffects();
        }

        // Check if the item is PurifiedSalt
        PurifiedSalt* salt = dynamic_cast<PurifiedSalt*>(holder->get_Object());
        if (salt != nullptr)
        {
            ++fSalt;
            feSalt = salt->get_ObjEffects();
        }

        // Move to the next item in the inventory
        holder = holder->get_Prev();
    }

    push("Quantity: " + to_string(fSalt));
    push("Effects: " + feSalt);
    push("Items: Purified Salt");
    push("---------------------------------");
    push("Quantity: " + to_string(fPotion));
    push("Effects: " + fePotion);
    push("Items: Sanity Potion");

}