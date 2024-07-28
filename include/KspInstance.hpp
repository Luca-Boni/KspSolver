#pragma once

#include "Item.hpp"
#include "AvailableItems.hpp"
#include "KspSolution.hpp"
#include <vector>
#include <iostream>
#include <fstream>

class KspInstance
{
private:
    int groupsNum;
    int itemsNum;
    int capacity;
    AvailableItems availableItems;

public:
    KspInstance(std::string filename);

    int GetGroupsNum();
    int GetItemsNum();
    int GetCapacity();
    AvailableItems GetAvailableItems();
    KspSolution GetInitialSolution();
    void Print();
};