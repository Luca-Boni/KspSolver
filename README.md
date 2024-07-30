# Knapsack Sharing Problem Solver

This is a solver for the Knapsack Sharing Problem (KSP). The KSP is a combinatorial optimization problem that arises in the context of the sharing of resources among a set of agents.

This solver implements the Late-Acceptance Hill-Climbing algorithm to find a solution to the KSP.

## How to compile

This program was written in C++ with Linux as the target platform. To compile it, simply run the `compile.sh` script.

## How to run

To run the program, execute `kspSolver` located in the `bin` directory. It takes three arguments:

- `instance_file`, the path to the input file (MANDATORY)
- `srand`, the seed for the random number generator (OPTIONAL, default is the current UNIX time)
- `k`, which is the size of the list that keeps the last values of the objective function (OPTIONAL, default is 20)
- `max_iterations`, the maximum number of iterations the program will run (OPTIONAL, default is 1000)

Examples:

```bash
./bin/kspSolver data/A02C
./bin/kspSolver data/A10 1
./bin/kspSolver data/B50 234 15
./bin/kspSolver data/B50 99999 20 1000
```

## Input format

The data folder already contains a few examples of input files. The format of the input file is as follows:

```
number_of_items
number_of_groups
knapsack_capacity
items_in_group_1 items_in_group_2 ... items_in_group_G
item_1_weight item_1_profit
item_2_weight item_2_profit
...
item_n_weight item_n_profit
```