#pragma once
#include "Player.h"  // Include the Player class to manage player-related data and interactions
#include <iostream>
#include <string>
using namespace std;

class Narrator
{
public:
    typedef Narrator Node;  // Define 'Node' as a type alias for the 'Narrator' class (for stack-like structure)
    Node* next;  // Pointer to the next node in the stack
    string message;  // The message that the narrator will display
    Player* player;  // Pointer to the player object, which may be used to interact with the player during narration

    // Default constructor for the Narrator class
    Narrator();

    // Parameterized constructor to initialize with a message and a player object
    Narrator(string msg, Player* player);

    // Destructor: Used to clean up memory and remove nodes from the stack
    ~Narrator();

    // Method to push a new message onto the stack
    void push(string msg);

    // Method to pop the top message from the stack
    void pop();

    // Method to peek at the top message and pop it from the stack
    string peekThenPop();

    // Method to retrieve and move to the next message in the stack
    string get_Next();

    // Method to check if the stack is empty
    bool isEmpty() const;

    // Various methods to manage specific game events and narrations
    void Introduction();  // The introduction message that starts the game
    void Pause();  // Display the pause menu options
    void AfterWakeUp();  // Narration after the player wakes up in the game

    // Methods for different rooms in the game, each with specific conditions or inventory checks
    void Hall(bool jacket);  // Narration for the hall room
    void Kitchen(bool potion, bool salt, bool clue1);  // Narration for the kitchen room, based on item conditions
    void Bathroom(bool potion, bool box);  // Narration for the bathroom room, based on item conditions
    void Entrance(bool keyInRoom, bool saltUsed);  // Narration for the entrance room, based on item conditions
    void Room1(bool key, bool firstTime);  // Narration for the first room, based on key and first-time conditions
    void Clue1();  // Display a clue in the game

    // Methods for displaying player information
    void SeeInventory();  // Display the player's inventory
    void PlayerStatus();  // Display the player's current status (e.g., sanity, health)
    void HelpScreen();  // Display the help screen with game instructions
    void GameOver();  // Display the game over message when the player loses
    void Winning();  // Display the winning message when the player succeeds

private:
    Node* top;  // Pointer to the top of the stack, used to manage the stack of messages
};
