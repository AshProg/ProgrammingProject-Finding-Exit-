#pragma once
#pragma once
#include <iostream>
#include <map>
#include <string>
#include <random>

class HiddenRoom
{
private:
    struct RoomNode
    {
        std::map<int, RoomNode*> choices; // Choices from the current room (e.g., 1, 2, 3)
        bool isCorrect;                   // Whether this is the correct path
    };

    RoomNode* root;     // Starting point of the hidden room
    RoomNode* current;  // Current room node
    int depth;          // Depth of the hidden room
    int maxDepth;       // Max depth for exploration
    int sanityLoss;     // Sanity reduction for wrong choices

    void GenerateRoom(RoomNode* node, int level)
    {
        if (level > maxDepth)
            return;

        // Create 3 choices for each room
        for (int i = 1; i <= 3; i++)
        {
            RoomNode* newNode = new RoomNode();
            newNode->isCorrect = false;
            node->choices[i] = newNode;
            GenerateRoom(newNode, level + 1);
        }

        // Randomly assign the correct choice for this level
        int correctChoice = rand() % 3 + 1;
        node->choices[correctChoice]->isCorrect = true;
    }

    void ClearRoom(RoomNode* node)
    {
        for (auto& [key, child] : node->choices)
        {
            ClearRoom(child);
            delete child;
        }
    }

public:
    HiddenRoom(int depth = 5, int sanityLoss = 10)
        : root(new RoomNode()), current(root), depth(0), maxDepth(depth), sanityLoss(sanityLoss)
    {
        root->isCorrect = true; // Root node starts as correct
        GenerateRoom(root, 1);
    }

    ~HiddenRoom()
    {
        ClearRoom(root);
    }

    bool EnterRoom(int choice)
    {
        if (current->choices.find(choice) != current->choices.end())
        {
            RoomNode* nextRoom = current->choices[choice];
            if (nextRoom->isCorrect)
            {
                current = nextRoom;
                depth++;
                std::cout << "Correct choice! Proceeding to the next room.\n";

                if (depth == maxDepth)
                {
                    std::cout << "You've reached the final room! You've successfully navigated the hidden rooms.\n";
                    return true; // Reached the end
                }
                return false; // Continue exploring
            }
        }

        // Wrong choice
        std::cout << "Wrong choice! Returning to the main room.\n";
        current = root;
        depth = 0;
        return false;
    }

    int GetSanityLoss() const
    {
        return sanityLoss;
    }
};
