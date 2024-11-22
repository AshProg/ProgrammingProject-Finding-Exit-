#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

class ImageRoom
{
public:
    typedef ImageRoom Node;  // Define Node type alias for ImageRoom, similar to Inventory class.
    static Node NIL;         // Static sentinel node, used to mark the end of the list.

private:
    Sprite sprite;  // Sprite representing the image for the room.
    Node* prev;     // Pointer to the previous node in the list.
    Node* next;     // Pointer to the next node in the list.

public:
    // Default constructor initializes the node to point to the NIL sentinel.
    ImageRoom()
    {
        next = &NIL;  // Set next pointer to NIL (end of list).
        prev = &NIL;  // Set previous pointer to NIL (start of list).
    }

    // Constructor that initializes the sprite and sets the next and previous pointers to NIL.
    ImageRoom(Sprite spr)
        : sprite(spr), next(&NIL), prev(&NIL) {}

    // Adds a new node after the current node in the linked list (enqueue).
    void Enqueue(Node* newNode)
    {
        newNode->prev = this;  // Set the previous pointer of the new node to the current node.

        if (this->next != &NIL)  // If there is a next node, link it to the new node.
        {
            newNode->next = this->next;
            this->next->prev = newNode;  // Update the previous pointer of the next node.
        }

        this->next = newNode;  // Set the current node's next pointer to the new node.
    }

    // Removes the current node from the linked list (dequeue).
    void Dequeue()
    {
        if (this->prev != &NIL)  // If the previous node is not NIL, update its next pointer.
        {
            this->prev->next = this->next;
        }

        if (this->next != &NIL)  // If the next node is not NIL, update its previous pointer.
        {
            this->next->prev = this->prev;
        }

        delete this;  // Delete the current node to free memory.
    }

    // Returns the sprite of the current node (ImageRoom).
    Sprite get_Sprite() const
    {
        return sprite;
    }

    // Returns the next node in the linked list.
    Node* get_Next()
    {
        return next;
    }

    // Returns the previous node in the linked list.
    Node* get_Prev()
    {
        return prev;
    }
};
