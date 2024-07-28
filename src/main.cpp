#include "KspInstance.hpp"
#include "KspSolver.hpp"
#include <iostream>
#include <filesystem>
#include <ctime>

#define K 20
#define MAX_ITERATIONS 100

using namespace std;

int main(int argc, char const *argv[]){

    string instanceFile = "./data/A02C";
    int k = K;
    int maxIterations = MAX_ITERATIONS;
    srand(time(NULL));

    if (argc < 2 || argc > 5)
    {
        cout << "Usage: " << argv[0] << " <instance_file> [srand] [k] [max_iterations]" << endl;
        // return 1;
    }

    if (argc >= 2)
    {
        instanceFile = argv[1];
    }

    if (argc >= 3)
    {
        srand(atoi(argv[2]));
    }

    if (argc >= 4)
    {
        k = atoi(argv[3]);
    }

    if (argc >= 5)
    {
        maxIterations = atoi(argv[4]);
    }

    KspInstance instance = KspInstance(instanceFile);
    KspSolver solver = KspSolver(instance, k);

    // instance.print();
    // solver.Print();
    solver.Solve(maxIterations);

    return 0;
}