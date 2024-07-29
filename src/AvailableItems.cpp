#include "AvailableItems.hpp"
#include "KspSolution.hpp"

AvailableItems::AvailableItems(int groupsNum, int itemsNum, int capacity, std::ifstream &file)
{
    this->groupsNum = groupsNum;
    this->itemsNum = itemsNum;
    this->capacity = capacity;
    items = std::vector<std::vector<Item>>(groupsNum);
    groupSizes = std::vector<int>(groupsNum);

    int groupSize;
    for (int group = 0; group < groupsNum; group++)
    {
        file >> groupSize;
        groupSizes[group] = groupSize;
        items[group].resize(groupSize);
    }

    int itemId = 0;
    for (int group = 0; group < groupsNum; group++)
    {
        for (int item = 0; item < items[group].size(); item++)
        {
            Item &toAdd = items[group][item];
            file >> toAdd.weight >> toAdd.profit;
            toAdd.group = group;
            toAdd.index = item;
            toAdd.id = itemId++;
        }
    }

    if (itemId != itemsNum)
    {
        throw std::runtime_error("Number of items not consistent!");
    }
}

std::string AvailableItems::ToString()
{
    std::string str = "";
    for (int group = 0; group < groupsNum; group++)
    {
        str += "Group " + std::to_string(group) + ": ";
        for (auto item : items[group])
        {
            str += item.ToString() + " ";
        }
        str += "\n";
    }

    return str;
}

KspSolution AvailableItems::GetInitialSolution()
{
    KspSolution solution(*this);
    return solution;
}

Item AvailableItems::GetNextItem(Item item)
{
    int group = item.group;
    int itemIndex = item.index;

    if (itemIndex == items[group].size() - 1)
    {
        group = (group + 1) % groupsNum;
        itemIndex = 0;
    }
    else
    {
        itemIndex++;
    }

    return items[group][itemIndex];
}

Item AvailableItems::GetItem(int id)
{
    int group;
    int idLeft = id;
    for (group = 0; group < groupsNum; group++)
    {
        if (idLeft < groupSizes[group])
        {
            return items[group][idLeft];
        }
        idLeft -= groupSizes[group];
    }

    throw std::runtime_error("Item not found!");
}