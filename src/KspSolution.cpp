#include "KspSolution.hpp"
#include "AvailableItems.hpp"

#include <unordered_set>
#include <tuple>
#include <iostream>

#define NEIGHBOR_DEGREE 3

KspSolution::KspSolution(AvailableItems &availableItems)
{
    this->availableItems = availableItems;
    int groupsNum = availableItems.GetGroupsNum();
    int itemsNum = availableItems.GetItemsNum();

    weight = 0;
    groupProfits = std::vector<int>(groupsNum, 0);

    selectedItems = std::unordered_set<Item, ItemHash>();
}

KspSolution::KspSolution(const KspSolution &solution)
{
    availableItems = solution.availableItems;
    weight = solution.weight;
    groupProfits = std::vector<int>(solution.groupProfits);

    selectedItems = std::unordered_set<Item, ItemHash>(solution.selectedItems);
}

std::vector<KspSolution> KspSolution::GetNeighbors(int n)
{
    std::vector<KspSolution> neighbors;
    int i = 0;

    while (i < n)
    {
        KspSolution neighbor(*this);
        int selectedItemsNum = (rand() % NEIGHBOR_DEGREE) + 1;

        for (int j = 0; j < selectedItemsNum; j++)
        {
            int itemId = rand() % availableItems.GetItemsNum();
            Item selectedItem = availableItems.GetItem(itemId);

            if (selectedItems.find(selectedItem) == selectedItems.end())
            {
                neighbor.groupProfits[selectedItem.group] += selectedItem.profit;
                neighbor.weight += selectedItem.weight;
                neighbor.selectedItems.insert(selectedItem);
            }
            else
            {
                neighbor.groupProfits[selectedItem.group] -= selectedItem.profit;
                neighbor.weight -= selectedItem.weight;
                neighbor.selectedItems.erase(selectedItem);
            }
        }

        if (neighbor.weight <= availableItems.GetCapacity())
        {
            neighbors.push_back(neighbor);
            i++;
        }
    }

    return neighbors;
}

std::unordered_set<Item, ItemHash> KspSolution::GetSelectedItems()
{
    return selectedItems;
}

std::string KspSolution::ToString()
{
    std::string str = "Selected Items: " + std::to_string(selectedItems.size()) + "\n";
    for (Item item : selectedItems)
    {
        str += item.ToString() + " ";
    }
    str += "\n";

    str += "Weight: " + std::to_string(weight) + "\n";
    str += "Group Profits: ";

    for (int profit : groupProfits)
    {
        str += std::to_string(profit) + " ";
    }
    str += "\n";

    str += "Value: " + std::to_string(GetValue());

    return str;
}