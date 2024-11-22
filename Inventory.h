#pragma once
#include "Objects.h"
#include "SanityPotion.h"
#include "PurifiedSalt.h"

// Inventory class to implement a doubly linked list structure for managing game objects
class Inventory
{
public:
    typedef Inventory Node; // Define Node as an alias for Inventory
    static Node NIL;        // Static NIL node used as a sentinel to mark the end of the list

private:
    Objects* object;        // Pointer to an object stored in this node
    Node* prev;             // Pointer to the previous node in the list
    Node* next;             // Pointer to the next node in the list

public:
    // Default constructor initializing the node to point to the NIL node
    Inventory()
    {
        next = &NIL;        // Next points to NIL
        prev = &NIL;        // Previous points to NIL
    }

    // Constructor to create a node with a specific object
    Inventory(Objects* obj)
    {
        object = obj;       // Store the passed object
        next = &NIL;        // Next points to NIL
        prev = &NIL;        // Previous points to NIL
    }

    // Add a new node before the current node in the doubly linked list
    void Add(Node* newNode)
    {
        newNode->next = this;               // Link new node's next to the current node
        if (this->prev != &NIL)            // If the current node is not the first node
        {
            newNode->prev = this->prev;    // Link new node's prev to current's previous node
            this->prev->next = newNode;    // Update the previous node's next pointer
        }
        this->prev = newNode;              // Update the current node's previous pointer
    }

    // Remove the current node from the doubly linked list
    void Remove()
    {
        if (this->prev != &NIL)            // If the current node is not the first node
        {
            this->prev->next = this->next; // Update the previous node's next pointer
        }

        if (this->next != &NIL)            // If the current node is not the last node
        {
            this->next->prev = this->prev; // Update the next node's previous pointer
        }

        delete this;                       // Deallocate memory for the current node
    }

    // Get the object stored in the current node
    Objects* get_Object()
    {
        return object;                     // Return the stored object
    }

    // Get the next node in the list
    Node* get_Next()
    {
        return next;                       // Return the next node
    }

    // Get the previous node in the list
    Node* get_Prev()
    {
        return prev;                       // Return the previous node
    }
};
