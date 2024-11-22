#pragma once
#include "Outwear.h"

// Singly Linked List for managing Outwear inventory
class OutwearInv
{
public:
    typedef OutwearInv Node;  // Defining the Node type for the linked list
    Node* next;               // Pointer to the next node in the list
    Outwear* fOutwear;        // Pointer to the Outwear object stored in the node

    // Default constructor initializes the list to be empty (current is nullptr)
    OutwearInv()
    {
        current = nullptr;  // No items in the inventory initially
    }

    // Constructor that initializes the list with a given Outwear item
    OutwearInv(Outwear* outwear)
    {
        fOutwear = outwear;  // Set the Outwear item
        next = nullptr;      // Set the next pointer to nullptr (no next node)
    }

    // Destructor that deletes all nodes in the list to prevent memory leaks
    ~OutwearInv()
    {
        Node* currentNode = current;  // Start from the current node (head of the list)

        // Iterate through all nodes and delete them one by one
        while (currentNode != nullptr)
        {
            Node* temp = currentNode;      // Save the current node temporarily
            currentNode = currentNode->next; // Move to the next node
            delete temp;                   // Delete the current node
        }
    }

    // Add a new Outwear item to the inventory list (add at the front)
    void Add(Outwear* outwear)
    {
        Node* newNode = new Node(outwear);  // Create a new node with the given Outwear
        newNode->next = current;            // Link the new node to the current head
        current = newNode;                  // Update the current head to the new node
    }

    // Remove the first node from the list (removes the oldest item)
    void Remove()
    {
        if (!isEmpty())  // Only remove if the list is not empty
        {
            Node* temp = current;  // Save the current head node temporarily
            current = current->next; // Update the head to the next node in the list
            delete temp;            // Delete the old head node
        }
    }

    // Check if the inventory list is empty
    bool isEmpty() const
    {
        return current == nullptr;  // If current is nullptr, the list is empty
    }

    // Retrieve the current Outwear item from the head node
    Outwear* get_Current()
    {
        Outwear* out = current->fOutwear;  // Get the Outwear item from the current head node
        return out;                        // Return the Outwear object
    }

private:
    Node* current;  // Pointer to the head node of the linked list (the current Outwear item)
};
