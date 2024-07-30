#include "KspSolver.hpp"
#include <algorithm>
#include <ctime>
#include <cstring>
#include <filesystem>

#define NEIGHBORHOOD_SIZE 100
// #define NEIGHBORHOOD_FACTOR 10

KspSolver::KspSolver(KspInstance &instance, int k) : instance(instance)
{
    this->k = k;

    curSolution = instance.GetInitialSolution();
    curIteration = 0;
    lastValues = new int[k];
    bzero(lastValues, k * sizeof(int));
    lastValuesLen = 0;

    bestSolution = curSolution;
    bestSolutionIteration = 0;

    finishTime = 0;
}

void KspSolver::PrintInstance()
{
    instance.Print();
}

void KspSolver::PrintLastValues()
{
    std::cout << "Last values: ";
    for (int i = 0; i < std::min(k, lastValuesLen); i++)
    {
        std::cout << lastValues[i] << " ";
    }
    std::cout << std::endl;
}

void KspSolver::PrintCurrentState()
{
    std::cout << "Current iteration: " << curIteration << std::endl
              << "Iteration the best solution was found: " << bestSolutionIteration << std::endl
              << "Time the best solution was found: " << (double)(bestSolutionTime - startTime) / CLOCKS_PER_SEC << "s" << std::endl
              << "Total time elapsed: " << (double)(clock() - startTime) / CLOCKS_PER_SEC << "s" << std::endl;
}

void KspSolver::PrintCurSolution()
{
    std::cout << "Current solution: " << std::endl
              << curSolution.ToString() << std::endl;
}

void KspSolver::PrintBestSolution()
{
    std::cout << "Time elapsed: " << (double)(bestSolutionTime - startTime) / CLOCKS_PER_SEC << "s" << std::endl
              << "Best solution: " << std::endl
              << bestSolution.ToString() << std::endl;
}

void KspSolver::PrintCurItems()
{
    std::cout << "Current items: " << std::endl;
    for (auto item : curSolution.GetSelectedItems())
    {
        std::cout << item.ToString() << std::endl;
    }
}

void KspSolver::PrintBestItems()
{
    std::cout << "Best items: " << std::endl;
    for (auto item : bestSolution.GetSelectedItems())
    {
        std::cout << item.ToString() << std::endl;
    }
}

void KspSolver::Iterate()
{
    curIteration++;

    std::vector<KspSolution> neighbors = curSolution.GetNeighbors(NEIGHBORHOOD_SIZE);
    lastValuesLen = std::min(k, lastValuesLen + 1);

    // for s' in N(s) do
    for (KspSolution neighbor : neighbors)
    {
        // if s' é melhor que última em L ou s' é melhor que s then
        if (neighbor.GetValue() > lastValues[0] || neighbor.GetValue() >= curSolution.GetValue())
        // ou se nem todos grupos foram selecionados ainda e colocou um grupo a mais
        // || (CurObjectiveFunction() == 0 && EmptyGroups(neighbour) < CurEmptyGroups()))
        {
            // s <- s'
            curSolution = neighbor;
            // insere s na frente de L
            // se length(L) > k then
            //   Remove último elemento de L
            if (curIteration <= k)
            {
                lastValues[curIteration - 1] = neighbor.GetValue();
            }
            else
            {
                memcpy(lastValues, lastValues + 1, (k - 1) * sizeof(int));
                lastValues[k - 1] = neighbor.GetValue();
            }
            // if s é melhor que s* then
            if (neighbor.GetValue() > bestSolution.GetValue())
            {
                // s* <- s
                bestSolution = neighbor;
                bestSolutionIteration = curIteration;
                bestSolutionTime = clock();
                // std::cout << "Found new best solution at iteration " << curIteration << std::endl;
                // PrintBestSolution();
            }
        }
    }
}

void KspSolver::Solve(int maxIterations)
{
    startTime = clock();
    bestSolutionTime = startTime;
    while (curIteration < maxIterations)
    {
        Iterate();
    }
    finishTime = clock();
    std::cout << "--------------------------------------------------------------------------------" << std::endl
              << "Program finished. " << std::endl;
    PrintBestSolution();
    std::cout << "Total time elapsed: " << GetFinishTime() << "s" << std::endl;
}