#pragma once
#include "Inventory.h"

class InventoryIterator
{
private:
    typedef Inventory Node;  // Type alias for Inventory node, similar to a linked list node.
    Node* current;  // Pointer to the current node (item) in the inventory.

public:
    // Constructor to initialize the iterator at the start node of the inventory.
    InventoryIterator(Node* start) : current(start) {}

    // Constructor to initialize the iterator to the node provided by reference (used for accessing sentinel).
    InventoryIterator(Node& node) : current(&node) {}

    // Pre-increment operator to move the iterator to the next node in the inventory (forward traversal).
    InventoryIterator& operator++()
    {
        current = current->get_Next();  // Move to the next node.
        return *this;  // Return the updated iterator.
    }

    // Post-increment operator (returns the iterator before incrementing).
    InventoryIterator& operator++(int)
    {
        InventoryIterator& temp = *this;  // Save the current state of the iterator.
        ++(*this);  // Perform the pre-increment operation.
        return temp;  // Return the iterator before incrementing.
    }

    // Pre-decrement operator to move the iterator to the previous node in the inventory (backward traversal).
    InventoryIterator& operator--()
    {
        current = current->get_Prev();  // Move to the previous node.
        return *this;  // Return the updated iterator.
    }

    // Post-decrement operator (returns the iterator before decrementing).
    InventoryIterator& operator--(int)
    {
        InventoryIterator& temp = *this;  // Save the current state of the iterator.
        --(*this);  // Perform the pre-decrement operation.
        return temp;  // Return the iterator before decrementing.
    }

    // Equality operator to compare two iterators.
    bool operator==(const InventoryIterator& other) const
    {
        return current == other.current;  // Return true if both iterators point to the same node.
    }

    // Inequality operator to compare two iterators.
    bool operator!=(const InventoryIterator& other) const
    {
        return current != other.current;  // Return true if iterators point to different nodes.
    }

    // Returns the object (item) pointed to by the iterator.
    Objects* getValue()
    {
        return current->get_Object();  // Return the object stored at the current node.
    }

    // Returns the current node (for accessing the node directly).
    Node* getCurrent()
    {
        return current;  // Return the pointer to the current node.
    }

    // Returns an iterator pointing to the first node in the inventory.
    InventoryIterator begin()
    {
        return InventoryIterator(current);  // Return an iterator at the start of the inventory.
    }

    // Returns an iterator pointing to the sentinel node (end marker).
    InventoryIterator end()
    {
        return InventoryIterator(Node::NIL);  // Return an iterator to the sentinel (end) node.
    }
};
