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

    Narrator(); 
    Narrator(string msg, Player* player);
    ~Narrator();
    void push(string msg);
    void pop();
    string peekThenPop();
    string get_Next();
    bool isEmpty() const;

    void Introduction();
    void Pause();
    void AfterWakeUp();
    void Hall();
    void Kitchen(bool potion, bool salt);
    void SeeInventory();
    void PlayerStatus();

private:
    Node* top;                         
};
