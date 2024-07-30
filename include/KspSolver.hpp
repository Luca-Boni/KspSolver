#pragma once

#include "KspInstance.hpp"
#include "KspSolution.hpp"
#include <vector>

class KspSolver
{
private:
    KspInstance instance;
    int k;

    KspSolution curSolution;
    int curIteration;
    int *lastValues;
    int lastValuesLen;

    KspSolution bestSolution;
    int bestSolutionIteration;

    clock_t startTime;
    clock_t bestSolutionTime;
    clock_t finishTime;

    void Iterate();
    void PrintCurrentState();
    void PrintCurSolution();
    void PrintBestSolution();
    void PrintInstance();

public:
    KspSolver(KspInstance &instance, int k);

    int GetCurValue() { return curSolution.GetValue(); }
    int GetBestValue() { return bestSolution.GetValue(); }

    std::vector<int> GetCurGroupsProfits() { return curSolution.GetGroupsProfits(); }
    std::vector<int> GetBestGroupsProfits() { return bestSolution.GetGroupsProfits(); }

    int GetCurWeight() { return curSolution.GetWeight(); }
    int GetBestWeight() { return bestSolution.GetWeight(); }

    int GetCurIteration() { return curIteration; }
    double GetFinishTime() { return finishTime == 0 ? 0 : (double)(finishTime - startTime) / CLOCKS_PER_SEC; }

    void PrintCurItems();
    void PrintBestItems();

    void PrintLastValues();

    void Solve(int maxIterations);
};