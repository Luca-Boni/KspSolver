#include "utilities.hpp"
#include "KspInstance.hpp"
#include "KspSolver.hpp"
#include <iostream>
#include <filesystem>

#define K 20
#define MAX_ITERATIONS 100

using namespace std;

int main(int argc, char const *argv[]){

    string instanceFile = "./data/A02C";
    int k = K;
    int maxIterations = MAX_ITERATIONS;

    if (argc < 2)
    {
        cout << "Usage: " << argv[0] << " <instance_file> [k] [max_iterations]" << endl;
        // return 1;
    }

    if (argc >= 2)
    {
        instanceFile = argv[1];
    }

    if (argc >= 3)
    {
        k = atoi(argv[2]);
    }

    if (argc >= 4)
    {
        maxIterations = atoi(argv[3]);
    }

    KspInstance instance = KspInstance(instanceFile);
    KspSolver solver = KspSolver(instance, k);

    // instance.print();
    solver.Print();
    // solver.solve(MAX_ITERATIONS);

    return 0;
}