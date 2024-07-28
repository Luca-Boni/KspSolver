#pragma once

#include "Item.hpp"
#include "AvailableItems.hpp"
#include <algorithm>
#include <vector>
#include <string>

class KspSolution
{
private:
    int weight;
    std::vector<int> groupProfits;
    std::vector<std::vector<bool>> selectedItems;
    AvailableItems availableItems;

public:
    KspSolution() {}
    KspSolution(AvailableItems &availableItems);
    KspSolution(const KspSolution &solution);

    std::vector<Item> GetSelectedItems();
    std::vector<KspSolution> GetNeighbors(int n);
    int GetWeight() { return weight; }
    std::vector<int> GetGroupsProfits() { return groupProfits; }
    int GetGroupProfit(int group) { return groupProfits[group]; }
    int GetValue() { return *std::min_element(groupProfits.begin(), groupProfits.end()); }

    std::string ToString();
};