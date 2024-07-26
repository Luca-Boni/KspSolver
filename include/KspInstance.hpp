#pragma once

#include <vector>
#include <iostream>
#include <fstream>

typedef struct Item
{
    int weight;
    int value;
} Item;

class KspInstance
{
private:
    int groupsNum;
    int itemsNum;
    int capacity;
    std::vector<std::vector<Item>> items;

public:
    int GetGroupsNum();
    int GetItemsNum();
    int GetCapacity();
    std::vector<std::vector<Item>> GetItems();

    void PrintItem(Item item);
    void PrintItems();
    void Print();

    KspInstance(int groupsNum, int itemsNum, int capacity, std::vector<std::vector<Item>> items);
    KspInstance(std::string filename);
    KspInstance();
};