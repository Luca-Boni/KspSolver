#include "KspInstance.hpp"

KspInstance::KspInstance(std::string filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error opening file " << filename << std::endl;
        exit(1);
    }

    file >> itemsNum >> groupsNum >> capacity;

    availableItems = AvailableItems(groupsNum, itemsNum, capacity, file);
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

AvailableItems KspInstance::GetAvailableItems()
{
    return availableItems;
}

KspSolution KspInstance::GetInitialSolution()
{
    return availableItems.GetInitialSolution();
}

void KspInstance::Print()
{
    std::cout << "Groups: " << groupsNum << std::endl
              << "Items: " << itemsNum << std::endl
              << "Capacity: " << capacity << std::endl
              << availableItems.ToString();
}