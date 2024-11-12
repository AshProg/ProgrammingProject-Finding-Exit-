#pragma once
#include "Inventory.h"

class InventoryIterator
{
private:
    typedef Inventory Node;
    Node* current;

public:
    InventoryIterator(Node* start) : current(start) {}

    // New constructor to access the sentinel in the iterator's end() method
    InventoryIterator(Node& node) : current(&node) {}

    // Pre-increment
    InventoryIterator& operator++()
    {
        current = current->get_Next();
        return *this;
    }

    // Post-increment
    InventoryIterator& operator++(int)
    {
        InventoryIterator& temp = *this;
        ++(*this);
        return temp;
    }

    // Pre-decrement
    InventoryIterator& operator--()
    {
        current = current->get_Prev();
        return *this;
    }

    // Post-decrement
    InventoryIterator& operator--(int)
    {
        InventoryIterator& temp = *this;
        --(*this);
        return temp;
    }

    bool operator==(const InventoryIterator& other) const
    {
        return current == other.current;
    }

    bool operator!=(const InventoryIterator& other) const
    {
        return current != other.current;
    }

    Objects* getValue()
    {
        return current->get_Object();
    }

    Node* getCurrent()
    {
        return current;
    }

    InventoryIterator begin()
    {
        return InventoryIterator(current);
    }

    InventoryIterator end()
    {
        return InventoryIterator(Node::NIL);  // Using NIL as the end marker
    }
};

