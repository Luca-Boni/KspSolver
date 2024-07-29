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
        return "(" + std::to_string(weight) + ", " + std::to_string(profit) + ", " + std::to_string(group) + ")";
    }

    bool operator==(const Item &other) const
    {
        return id == other.id;
    }

} Item;

struct ItemHash
{
    size_t operator()(const Item &item) const
    {
        return std::hash<int>()(item.id);
    }
};