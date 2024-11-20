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
        delete temp;
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
    top = top->next; 
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
    push(">> Bathroom");
    push(">> Kitchen");
    push(">> Room 1");
    push("");
    push("What you would do now? (Write your option)");
    push("When you try to open it, it is locked. You need a Key!");
    push("You wander around and saw the entrance door.");
    push("the kitchen and the bathroom");
    push("Outside is the hall. From the hall you can see the 2 rooms, ");
}

void Narrator::Kitchen(bool potion, bool salt, bool clue1)
{
    if (potion && salt && clue1)
    {
        push(">> Piece of Paper [PAPER]");
        push(">> Sanity Potion [POTION]");
        push(">> Purified Salt [SALT]");
        push("");
        push("On the table there are some things that you can pick up");
        push("Searching for anything that could be of help");
        push("You wanders in the kitchen for a while");
        push("Everything in the kitchen are very messy!");
        push("");
        push("Type \"BACK\" to go back to the HALL");
    }
    else if (!potion && salt && clue1)
    {
        push(">> Piece of Paper [PAPER]");
        push(">> Purified Salt [SALT]");
        push("");
        push("On the table there are some things that you can pick up");
        push("Searching for anything that could be of help");
        push("You wanders in the kitchen for a while");
        push("Everything in the kitchen are very messy!");
        push("");
        push("Type \"BACK\" to go back to the HALL");
    }
    else if (!potion && !salt && clue1)
    {
        push(">> Piece of Paper [PAPER]");
        push("");
        push("On the table there are some things that you can pick up");
        push("Searching for anything that could be of help");
        push("You wanders in the kitchen for a while");
        push("Everything in the kitchen are very messy!");
        push("");
        push("Type \"BACK\" to go back to the HALL");
    }
    else if (!potion && !salt && !clue1)
    {
        push("There are nothing left in the kitchen");
        push("");
        push("Searching for anything that could be of help");
        push("You wanders in the kitchen for a while");
        push("Everything in the kitchen are very messy!");
        push("");
        push("Type \"BACK\" to go back to the HALL");
    }
    else if (potion && !salt && clue1)
    {
        push(">> Piece of Paper [PAPER]");
        push(">> Sanity Potion [POTION]");
        push("");
        push("On the table there are some things that you can pick up");
        push("Searching for anything that could be of help");
        push("You wanders in the kitchen for a while");
        push("Everything in the kitchen are very messy!");
        push("");
        push("Type \"BACK\" to go back to the HALL");
    }
    else if (potion && !salt && !clue1)
    {
        push(">> Sanity Potion [POTION]");
        push("");
        push("On the table there are some things that you can pick up");
        push("Searching for anything that could be of help");
        push("You wanders in the kitchen for a while");
        push("Everything in the kitchen are very messy!");
        push("");
        push("Type \"BACK\" to go back to the HALL");
    }
    else if (potion && salt && !clue1)
    {
        push(">> Sanity Potion [POTION]");
        push(">> Purified Salt [SALT]");
        push("");
        push("On the table there are some things that you can pick up");
        push("Searching for anything that could be of help");
        push("You wanders in the kitchen for a while");
        push("Everything in the kitchen are very messy!");
        push("");
        push("Type \"BACK\" to go back to the HALL");
    }
    else if (!potion && salt && !clue1)
    {
        push(">> Purified Salt [SALT]");
        push("");
        push("On the table there are some things that you can pick up");
        push("Searching for anything that could be of help");
        push("You wanders in the kitchen for a while");
        push("Everything in the kitchen are very messy!");
        push("");
        push("Type \"BACK\" to go back to the HALL");
    }
    
}

void Narrator::Bathroom(bool potion, bool box)
{
    if (potion && box)
    {
        push(">> A Box [BOX] (Can only be OPEN)");
        push(">> Sanity Potion [POTION]");
        push("");
        push("Would you pick these items?");
        push("In the dark, you saw some items");
        push("There might be another clue you can find in here");
        push("In the bathroom, you saw blood splatter everywhere!");
        push("");
        push("Type \"BACK\" to go back to the HALL");
    }
    else if (!potion && box)
    {
        push(">> A Box [BOX]");
        push("");
        push("Would you pick this item?");
        push("In the dark, you an item");
        push("There might be another clue you can find in here");
        push("In the bathroom, you saw blood splatter everywhere!");
        push("");
        push("Type \"BACK\" to go back to the HALL");
    }
    else if (potion && !box)
    {
        push(">> Sanity Potion [POTION]");
        push("");
        push("Would you pick this item?");
        push("In the dark, you an item");
        push("There might be another clue you can find in here");
        push("In the bathroom, you saw blood splatter everywhere!");
        push("");
        push("Type \"BACK\" to go back to the HALL");
    }
    else
    {
        push("This bathroom is as empty as cobbler's curse");
        push("there are nothing for you to take in here.");
        push("In the bathroom, you saw blood splatter everywhere!");
        push("");
        push("Type \"BACK\" to go back to the HALL");
    }
}

void Narrator::Room1(bool key, bool firstTime)
{
    if (key && firstTime)
    {
        push(">> Key for the entrance [KEY]");
        push("");
        push("You should take it and go out of this place now!");
        push("It's the key for your freedom!");
        push("You entered the room from before. From afar you saw something shiny");
        push("");
        push("Type \"BACK\" to go back to the HALL");
    }
    else if (!key && firstTime)
    {
        push("Still this room looks veryyyyy creepy");
        push("There is no way the key would not be here right.");
        push("Maybe you need to do something first?");
        push("There is nothing to be seen in this room");
        push("");
        push("Type \"BACK\" to go back to the HALL");
    }
    else if (key && !firstTime)
    {
        push("and yet here you are still entering this room!");
        push("There are nothing more you can do inside this room");
        push("What are you looking for in this room?");
        push("");
        push("Type \"BACK\" to go back to the HALL");
    }
    else
    {
        push("You must get out as soon as possible!");
        push("Something jumps over you and scared you.");
        push("I WILL TAKE OVER YOU IN NO TIME!\"");
        push("NOTHING IS FREE IN THIS WORLD!");
        push("\"EVERYTHING COMES FOR A PRICE!");
        push("");
        push("Type \"BACK\" to go back to the HALL");
    }
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

void Narrator::PlayerStatus()
{
    push("Sanity Level: " + to_string(player->get_Sanity()));
    push("You need to get out as soon as possible!");
    push("Description: You are this person!");
    push("Player's Name: " + player->get_Name());
}

void Narrator::HelpScreen()
{
    push("4. Press \"Ctrl+P\" to pause the game");
    push("3. To open an object simply do the same as \"1\" but with \"OPEN\"");
    push("Example: You want to enter kitchen just type \"KITCHEN\"");
    push("2. To enter a room just type the room name");
    push("Simply type \"PICK SALT\" to pick the salt");
    push("Example: Purification Salt [SALT]");
    push("Use the short item name which can be seen besides the item name");
    push("1. To pick an items simply type \"PICK\" followed by item name");
    push("-----------------------------------------------------------------------------");
    push("LIST OF COMMANDS");
}
