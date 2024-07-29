#pragma once

#include "Item.hpp"

#include <vector>
#include <fstream>

class KspSolution;

class AvailableItems
{
private:
    int groupsNum;
    int itemsNum;
    int capacity;
    std::vector<int> groupSizes;
    std::vector<std::vector<Item>> items; // items[group][item_index]
public:
    AvailableItems() {}
    AvailableItems(int groupsNum, int itemsNum, int capacity, std::ifstream &file);

    int GetGroupsNum() { return groupsNum; }
    int GetGroupSize(int group) { return groupSizes[group]; }
    int GetItemsNum() { return itemsNum; }
    int GetCapacity() { return capacity; }
    std::vector<std::vector<Item>> GetItems() { return items; };

    Item GetItem(int group, int item) { return items[group][item]; }
    Item GetItem(int id);
    Item GetNextItem(Item item);

    std::string ToString();

    KspSolution GetInitialSolution();
};