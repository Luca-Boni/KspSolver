#include "KspInstance.hpp"
#include "KspSolver.hpp"
#include "KspSolution.hpp"
#include <iostream>
#include <filesystem>
#include <ctime>

#define K 20
#define MAX_ITERATIONS 100

using namespace std;

int main(int argc, char const *argv[]){

    string instanceFile = "";
    int k = K;
    int maxIterations = MAX_ITERATIONS;
    int randomSeed = time(NULL);

    if (argc < 2 || argc > 5)
    {
        cout << "Usage: " << argv[0] << " <instance_file> [srand] [k] [max_iterations]" << endl;
        return 1;
    }

    if (argc >= 2)
    {
        instanceFile = argv[1];
    }

    if (argc >= 3)
    {
        randomSeed = atoi(argv[2]);
    }

    if (argc >= 4)
    {
        k = atoi(argv[3]);
    }

    if (argc >= 5)
    {
        maxIterations = atoi(argv[4]);
    }

    KspSolution::randomSeed = randomSeed;
    KspSolution::generator = std::default_random_engine(randomSeed);

    KspInstance instance = KspInstance(instanceFile);
    KspSolver solver = KspSolver(instance, k);

    // instance.print();
    // solver.Print();
    solver.Solve(maxIterations);

    return 0;
}