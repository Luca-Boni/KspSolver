#pragma once

#include "KspInstance.hpp"

class KspSolver
{
private:
    KspInstance instance;
    int curWeight;
    int curValue;
    std::vector<int> curValues;
    std::vector<std::vector<bool>> curSolution;
    std::vector<std::vector<bool>> bestSolution;
    int k;
    int* lastValues;
    int lastValuesLen;
    int curIteration;
    int bestSolutionIteration;
    clock_t startTime;
    clock_t bestSolutionTime;

    int GetItemsValue(std::vector<std::vector<bool>> items);
    std::vector<int> GetItemsValues(std::vector<std::vector<bool>> items);
    int EmptyGroups(std::vector<std::vector<bool>> items);
    int GetItemsWeight(std::vector<std::vector<bool>> items);
    int ObjectiveFunction(std::vector<std::vector<bool>> items);
    void PrintItems(std::vector<std::vector<bool>> items);
    std::vector<std::vector<std::vector<bool>>> GetNeighbours();

    int CurEmptyGroups();

    void Iterate();
    void PrintSolution();
    void PrintInstance();

public:
    KspSolver(KspInstance instance, int k);
    KspSolver();

    int GetCurItemsValue();
    std::vector<int> GetCurItemsValues();
    int GetCurItemsWeight();
    int GetCurWeight();
    int GetCurIteration();

    void PrintCurItems();
    void PrintLastValues();
    void Print();
    int CurObjectiveFunction();

    void Solve(int maxIterations);
};