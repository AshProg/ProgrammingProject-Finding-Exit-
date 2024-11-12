#pragma once
#include "Objects.h"
#include "SanityPotion.h"
#include "PurifiedSalt.h"

class Inventory
{
public:
	typedef Inventory Node;
	static Node NIL;

private:
	Objects* object;
	Node* prev;
	Node* next;

public:
	Inventory()
	{
		next = &NIL;
		prev = &NIL;
	}

	Inventory(Objects* obj)
	{
		object = obj;
		next = &NIL;
		prev = &NIL;
	}

	void Add(Node* newNode)
	{
		newNode->next = this;
		if (this->prev != &NIL)
		{
			newNode->prev = this->prev;
			this->prev->next = newNode;
		}
		this->prev = newNode;
	}

	void Remove()
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

	Objects* get_Object()
	{
		return object;
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

