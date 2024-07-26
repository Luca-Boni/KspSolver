#include "KspSolver.hpp"
#include <algorithm>
#include <ctime>
#include <cstring>
#include <filesystem>
#include "utilities.hpp"

KspSolver::KspSolver(KspInstance instance, int k)
{
    this->instance = instance;
    this->curWeight = 0;
    this->curSolution.resize(instance.GetGroupsNum());
    this->curIteration = 1;
    this->bestSolutionIteration = 1;
    for (int group = 0; group < instance.GetGroupsNum(); group++)
    {
        this->curSolution[group].resize(instance.GetItems()[group].size());
        for (int item = 0; item < instance.GetItems()[group].size(); item++)
        {
            this->curSolution[group][item] = false;
        }
    }
    this->k = k;
    this->lastValues = new int[k];
    this->lastValuesLen = 0;
    this->bestSolution.resize(instance.GetGroupsNum());
    std::copy(this->curSolution.begin(), this->curSolution.end(), this->bestSolution.begin());
}

KspSolver::KspSolver()
{
    this->instance = KspInstance();
    this->curWeight = 0;
    this->curSolution = std::vector<std::vector<bool>>();
    this->curIteration = 1;
    this->k = 1;
    this->lastValues = nullptr;
    this->lastValuesLen = 0;
    this->bestSolution = std::vector<std::vector<bool>>();
    std::copy(this->curSolution.begin(), this->curSolution.end(), this->bestSolution.begin());
}

int KspSolver::GetItemsValue(std::vector<std::vector<bool>> items)
{
    int value = 0;
    for (int group = 0; group < this->instance.GetGroupsNum(); group++)
    {
        for (int item = 0; item < this->instance.GetItems()[group].size(); item++)
        {
            if (items[group][item])
            {
                value += this->instance.GetItems()[group][item].value;
            }
        }
    }
    return value;
}

int KspSolver::GetCurItemsValue()
{
    return GetItemsValue(this->curSolution);
}

std::vector<int> KspSolver::GetItemsValues(std::vector<std::vector<bool>> items)
{
    std::vector<int> values;
    values.resize(this->instance.GetGroupsNum());
    for (int group = 0; group < this->instance.GetGroupsNum(); group++)
    {
        values[group] = 0;
        for (int item = 0; item < this->instance.GetItems()[group].size(); item++)
        {
            if (items[group][item])
            {
                values[group] += this->instance.GetItems()[group][item].value;
            }
        }
    }
    return values;
}

std::vector<int> KspSolver::GetCurItemsValues()
{
    return GetItemsValues(this->curSolution);
}

int KspSolver::GetItemsWeight(std::vector<std::vector<bool>> items)
{
    int weight = 0;
    for (int group = 0; group < this->instance.GetGroupsNum(); group++)
    {
        for (int item = 0; item < instance.GetItems()[group].size(); item++)
        {
            if (items[group][item])
            {
                weight += this->instance.GetItems()[group][item].weight;
            }
        }
    }
    return weight;
}

int KspSolver::GetCurItemsWeight()
{
    return GetItemsWeight(this->curSolution);
}

int KspSolver::GetCurWeight()
{
    return this->curWeight;
}

int KspSolver::GetCurIteration()
{
    return this->curIteration;
}

void KspSolver::PrintInstance()
{
    this->instance.Print();
}

void KspSolver::PrintItems(std::vector<std::vector<bool>> items)
{
    for (int group = 0; group < this->instance.GetGroupsNum(); group++)
    {
        std::cout << "  Group " << group << ": ";
        for (int item = 0; item < this->instance.GetItems()[group].size(); item++)
        {
            if (items[group][item])
            {
                this->instance.PrintItem(this->instance.GetItems()[group][item]);
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}

void KspSolver::PrintCurItems()
{
    PrintItems(this->curSolution);
}

void KspSolver::PrintLastValues()
{
    std::cout << "Last values: ";
    for (int i = 0; i < std::min(this->k, this->lastValuesLen); i++)
    {
        std::cout << this->lastValues[i] << " ";
    }
    std::cout << std::endl;
}

void KspSolver::Print()
{
    std::vector<int> values = GetItemsValues(bestSolution);
    int totalValue = 0;

    std::cout << "Current iteration: " << this->curIteration << std::endl;
    this->PrintLastValues();
    std::cout << "Best solution so far: " << std::endl;
    std::cout << "Selected items: " << std::endl;
    this->PrintItems(bestSolution);
    std::cout << "Total weight: " << GetItemsWeight(bestSolution) << std::endl;
    std::cout << "Value per group: " << std::endl;

    for (int group = 0; group < this->instance.GetGroupsNum(); group++)
    {
        std::cout << "  Group " << group << ": " << values[group] << std::endl;
        totalValue += values[group];
    }

    std::cout << "Total value: " << totalValue << std::endl;
    std::cout << "Objective function: " << ObjectiveFunction(bestSolution) << std::endl;
    std::cout << "Iteration it was found: " << this->bestSolutionIteration << std::endl; 
    std::cout << "Time elapsed: " << (double)(this->bestSolutionTime - this->startTime) / CLOCKS_PER_SEC << "s" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    std::cout << "Current solution: " << std::endl;
    std::cout << "Selected items: " << std::endl;
    this->PrintCurItems();
    std::cout << "Total weight: " << GetCurItemsWeight() << std::endl;
    std::cout << "Value per group: " << std::endl;
    values = GetCurItemsValues();
    std::cout << "Total value: " << GetCurItemsValue() << std::endl;
    for (int group = 0; group < this->instance.GetGroupsNum(); group++)
    {
        std::cout << "  Group " << group << ": " << values[group] << std::endl;
    }
    std::cout << "Objective function: " << CurObjectiveFunction() << std::endl;
    std::cout << "================================" << std::endl;
}

int KspSolver::ObjectiveFunction(std::vector<std::vector<bool>> items)
{
    std::vector<int> values = GetItemsValues(items);
    return *(std::min_element(values.begin(), values.end()));
}

int KspSolver::CurObjectiveFunction()
{
    return ObjectiveFunction(this->curSolution);
}

int KspSolver::EmptyGroups(std::vector<std::vector<bool>> items)
{
    int emptyGroups = 0;
    for (int group = 0; group < this->instance.GetGroupsNum(); group++)
    {
        bool empty = true;
        for (int item = 0; item < this->instance.GetItems()[group].size(); item++)
        {
            if (items[group][item])
            {
                empty = false;
                break;
            }
        }
        if (empty)
            emptyGroups++;
    }
    return emptyGroups;
}

int KspSolver::CurEmptyGroups()
{
    return EmptyGroups(this->curSolution);
}

std::vector<std::vector<std::vector<bool>>> KspSolver::GetNeighbours()
{
    std::vector<std::vector<bool>> neighbour;
    std::vector<std::tuple<bool, std::vector<std::vector<bool>>>> neighbours;

    int totalNeighboursNum = this->instance.GetItemsNum();

    neighbours.resize(totalNeighboursNum);
    for (int i = 0; i < totalNeighboursNum; i++)
    {
        std::get<1>(neighbours[i]) = this->curSolution;
        // Inverts the state of the i-th item int the 3D array, so it generates all unique neighbours
        std::get<1>(neighbours[i])[i / this->instance.GetItems()[0].size()][i % this->instance.GetItems()[0].size()] = !this->curSolution[i / this->instance.GetItems()[0].size()][i % this->instance.GetItems()[0].size()];
        // If the weight exceeds the capacity, the neighbour is not valid
        if (GetCurItemsWeight() > this->instance.GetCapacity())
            std::get<0>(neighbours[i]) = false;
        else
            std::get<0>(neighbours[i]) = true;
    }

    for (int i = 0; i < totalNeighboursNum; i++)
    {
        if (!std::get<0>(neighbours[i]))
        {
            neighbours.erase(neighbours.begin() + i);
            i--;
            totalNeighboursNum--;
        }
    }

    std::vector<std::vector<std::vector<bool>>> validNeighbours;
    validNeighbours.resize(totalNeighboursNum);
    for (int i = 0; i < totalNeighboursNum; i++)
    {
        validNeighbours[i] = std::get<1>(neighbours[i]);
    }

    return validNeighbours;
}

void KspSolver::Iterate()
{
    std::vector<std::vector<std::vector<bool>>> neighbours = GetNeighbours();
    lastValuesLen = std::min(this->k, this->lastValuesLen + 1);

    // for s' in N(s) do
    for (auto neighbour : neighbours)
    {
        int neighbourValue = ObjectiveFunction(neighbour);
        // if s' é melhor que última em L ou s' é melhor que s then
        if (neighbourValue > this->lastValues[0] || neighbourValue > CurObjectiveFunction() ||
            // ou se nem todos grupos foram selecionados ainda e colocou um grupo a mais
            (CurObjectiveFunction() == 0 && EmptyGroups(neighbour) < CurEmptyGroups()))
        {
            // s <- s'
            this->curSolution = neighbour;
            // insere s na frente de L
            if (this->curIteration <= this->k)
                this->lastValues[this->curIteration - 1] = neighbourValue;
            else
            {
                memcpy(this->lastValues, this->lastValues + 1, (this->k - 1) * sizeof(int));
                this->lastValues[this->k - 1] = neighbourValue;
            }
            // if s é melhor que s* then
            if (neighbourValue > ObjectiveFunction(this->bestSolution)){
                // s* <- s
                std::copy(this->curSolution.begin(), this->curSolution.end(), this->bestSolution.begin());
                this->bestSolutionIteration = this->curIteration;
                this->bestSolutionTime = clock();
            }
        }
    }

    this->curValue = GetCurItemsValue();
    this->curWeight = GetCurItemsWeight();
    this->curIteration++;
}

void KspSolver::Solve(int maxIterations)
{
    this->startTime = clock();
    this->bestSolutionTime = this->startTime;
    while (this->curIteration < maxIterations)
    {
        clearScreen();
        Print();
        Iterate();
    }
    PrintSolution();
}

void KspSolver::PrintSolution()
{
    std::cout << "Best solution: " << std::endl;

    PrintItems(this->bestSolution);
    std::cout << "Total weight: " << GetItemsWeight(this->bestSolution) << std::endl;

    std::vector<int> values = GetItemsValues(this->bestSolution);
    std::cout << "Value per group: " << std::endl;
    for (int group = 0; group < this->instance.GetGroupsNum(); group++)
    {
        std::cout << "Group " << group << ": " << values[group] << std::endl;
    }
    std::cout << "Total value: " << GetItemsValue(this->bestSolution) << std::endl;
    std::cout << "Objective function: " << ObjectiveFunction(this->bestSolution) << std::endl;
    std::cout << "Total time elapsed: " << (double)(clock() - this->startTime) / CLOCKS_PER_SEC << "s" << std::endl;
}