#pragma once

#include "Item.hpp"
#include "AvailableItems.hpp"
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_set>
#include <random>

class KspSolution
{
private:
    int weight;
    std::vector<int> groupProfits;
    std::unordered_set<Item, ItemHash> selectedItems;
    AvailableItems availableItems;

public:
    inline static int randomSeed;
    inline static std::default_random_engine generator;

    KspSolution() {}
    KspSolution(AvailableItems &availableItems);
    KspSolution(const KspSolution &solution);

    std::unordered_set<Item, ItemHash> GetSelectedItems();
    std::vector<KspSolution> GetNeighbors(int n);
    int GetWeight() { return weight; }
    std::vector<int> GetGroupsProfits() { return groupProfits; }
    int GetGroupProfit(int group) { return groupProfits[group]; }
    int GetValue() { return *std::min_element(groupProfits.begin(), groupProfits.end()); }

    std::string ToString();
};