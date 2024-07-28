#pragma once

#include <string>

typedef struct Item
{
    int id;
    int group;
    int index;
    int weight;
    int profit;

    std::string ToString()
    {
        return "(" + std::to_string(weight) + ", " + std::to_string(profit) + ")";
    }

} Item;