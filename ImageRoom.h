#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

class ImageRoom
{
public:
    typedef ImageRoom Node;  // Define Node type alias, similar to Inventory class
    static Node NIL;         // Static sentinel node

private:
    Sprite sprite;  // Room's sprite
    Node* prev;     // Pointer to the previous node
    Node* next;     // Pointer to the next node

public:
    ImageRoom()
    {
        next = &NIL;
        prev = &NIL;
    }

    ImageRoom(Sprite spr)
        : sprite(spr), next(&NIL), prev(&NIL) {}

    void Enqueue(Node* newNode)
    {
        newNode->prev = this;
        if (this->next != &NIL)
        {
            newNode->next = this->next;
            this->next->prev = newNode;
        }
        this->next = newNode;
    }

    void Dequeue()
    {
        if (this->prev != &NIL)
        {
            this->prev->next = this->next;
        }

        if (this->next != &NIL)
        {
            this->next->prev = this->prev;
        }

        delete this;
    }

    Sprite get_Sprite() const
    {
        return sprite;
    }

    Node* get_Next()
    {
        return next;
    }

    Node* get_Prev()
    {
        return prev;
    }
};

// Definition of static NIL sentinel
ImageRoom::Node ImageRoom::NIL;
