#include "KspSolution.hpp"
#include "AvailableItems.hpp"

#include <unordered_set>
#include <tuple>
#include <iostream>

KspSolution::KspSolution(AvailableItems &availableItems)
{
    this->availableItems = availableItems;
    int groupsNum = availableItems.GetGroupsNum();
    int itemsNum = availableItems.GetItemsNum();

    weight = 0;
    groupProfits = std::vector<int>(groupsNum, 0);

    selectedItems = std::vector<std::vector<bool>>(groupsNum);

    for (int group = 0; group < groupsNum; group++)
    {
        selectedItems[group] = std::vector<bool>(availableItems.GetGroupSize(group), false);
        for (int item = 0; item < availableItems.GetGroupSize(group); item++)
        {
            selectedItems[group][item] = false;
        }
    }
}

KspSolution::KspSolution(const KspSolution &solution)
{
    availableItems = solution.availableItems;
    weight = solution.weight;
    groupProfits = std::vector<int>(solution.groupProfits);
    
    selectedItems = std::vector<std::vector<bool>>(solution.selectedItems.size());

    for (int group = 0; group < selectedItems.size(); group++)
    {
        selectedItems[group] = std::vector<bool>(solution.selectedItems[group].size());
        for (int item = 0; item < selectedItems[group].size(); item++)
        {
            selectedItems[group][item] = solution.selectedItems[group][item];
        }
    }
}

std::vector<KspSolution> KspSolution::GetNeighbors(int n)
{
    std::vector<KspSolution> neighbors;
    std::vector<bool> neighboursTried = std::vector<bool>(availableItems.GetItemsNum(), false);

    int i = 0;

    while (i < n)
    {
        KspSolution neighbor(*this);
        int group = rand() % selectedItems.size();
        int item = rand() % selectedItems[group].size();
        Item selectedItem = availableItems.GetItem(group, item);
        int originalId = selectedItem.id;
        bool looped = false;

        while (neighboursTried[selectedItem.id])
        {
            selectedItem = availableItems.GetNextItem(selectedItem);
            if (selectedItem.id == originalId)
            {
                looped = true;
                break;
            }
        }

        if (looped)
        {
            break;
        }

        neighboursTried[selectedItem.id] = true;

        if (neighbor.selectedItems[group][item])
        {
            neighbor.groupProfits[group] -= selectedItem.profit;
            neighbor.weight -= selectedItem.weight;
            neighbor.selectedItems[group][item] = false;
        }
        else
        {
            neighbor.groupProfits[group] += selectedItem.profit;
            neighbor.weight += selectedItem.weight;
            neighbor.selectedItems[group][item] = true;
        }

        if (neighbor.weight <= availableItems.GetCapacity())
        {
            neighbors.push_back(neighbor);
            i++;
        }
    }

    return neighbors;
}

std::vector<Item> KspSolution::GetSelectedItems()
{
    std::vector<Item> selectedItems;
    for (int group = 0; group < this->selectedItems.size(); group++)
    {
        for (int item = 0; item < this->selectedItems[group].size(); item++)
        {
            if (this->selectedItems[group][item])
            {
                selectedItems.push_back(availableItems.GetItem(group, item));
            }
        }
    }

    return selectedItems;
}

std::string KspSolution::ToString()
{
    std::string str = "Selected Items: ";
    for (Item item : GetSelectedItems())
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