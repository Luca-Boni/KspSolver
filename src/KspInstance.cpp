#include "KspInstance.hpp"

KspInstance::KspInstance(int groupsNum, int itemsNum, int capacity, std::vector<std::vector<Item>> items)
{
    this->groupsNum = groupsNum;
    this->itemsNum = itemsNum;
    this->capacity = capacity;
    this->items = items;
}

KspInstance::KspInstance(std::string filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error opening file " << filename << std::endl;
        exit(1);
    }

    file >> itemsNum >> groupsNum >> capacity;

    items.resize(groupsNum);

    int groupSize;
    for (int group = 0; group < groupsNum; group++)
    {
        file >> groupSize;
        items[group].resize(groupSize);
    }

    for (int group = 0; group < groupsNum; group++)
    {
        for (int item = 0; item < items[group].size(); item++)
        {
            file >> items[group][item].weight >> items[group][item].value;
        }
    }
}

KspInstance::KspInstance()
{
    this->groupsNum = 0;
    this->itemsNum = 0;
    this->capacity = 0;
    this->items = std::vector<std::vector<Item>>();
}

int KspInstance::GetGroupsNum()
{
    return groupsNum;
}

int KspInstance::GetItemsNum()
{
    return itemsNum;
}

int KspInstance::GetCapacity()
{
    return capacity;
}

std::vector<std::vector<Item>> KspInstance::GetItems()
{
    return items;
}

void KspInstance::PrintItem(Item item)
{
    std::cout << "(" << item.weight << ", " << item.value << ")";
}

void KspInstance::PrintItems()
{
    for (int group = 0; group < groupsNum; group++)
    {
        std::cout << "Group " << group << ": ";
        for (auto item : items[group])
        {
            PrintItem(item);
            std::cout << " ";
        }
        std::cout << std::endl;
    }
}

void KspInstance::Print()
{
    std::cout << "Groups: " << groupsNum << std::endl;
    std::cout << "Items: " << itemsNum << std::endl;
    std::cout << "Capacity: " << capacity << std::endl;
    PrintItems();
}