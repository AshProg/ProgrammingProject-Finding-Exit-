#pragma once
#include "Outwear.h"

// Singly Linked List
class OutwearInv
{
public:
	typedef OutwearInv Node;
	Node* next;
	Outwear* fOutwear;

	OutwearInv()
	{
		current = nullptr;
	}

	OutwearInv(Outwear* outwear)
	{
		fOutwear = outwear;
		next = nullptr;
	}

	~OutwearInv()
	{
		Node* currentNode = current;
		while (currentNode != nullptr)
		{
			Node* temp = currentNode;
			currentNode = currentNode->next;
			delete temp;
		}
	}

	void Add(Outwear* outwear)
	{
		Node* newNode = new Node(outwear);
		newNode->next = current;
		current = newNode;
	}

	void Remove()
	{
		if (!isEmpty())
		{
			Node* temp = current;
			current = current->next;
			delete temp;
		}
	}

	bool isEmpty() const
	{
		return current == nullptr;
	}

	Outwear* get_Current()
	{
		Outwear* out = current->fOutwear;
		return out;
	}

private:
	Node* current;
};