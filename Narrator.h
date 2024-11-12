#pragma once
#include "Player.h"
#include <iostream>
#include <string>
using namespace std;

class Narrator
{
public:
    typedef Narrator Node;
    Node* next;
    string message;
    Player* player;

    Narrator();                         // Constructor
    Narrator(string msg, Player* player);               // Parameterized constructor for nodes
    ~Narrator();
    void push(string msg);              // Push a new message onto the stack
    void pop();                         // Pop the top message from the stack
    string peekThenPop();                // View the top message without removing
    string get_Next();
    bool isEmpty() const;               // Check if the stack is empty

    void Introduction();
    void Pause();
    void AfterWakeUp();
    void Hall();
    void SeeInventory();

private:
    Node* top;                         
};
