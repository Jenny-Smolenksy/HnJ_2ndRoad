#include <iostream>
#include "cache/FileCacheManager.h"
#include "problem_solve/StringRevrser.h"

int main() {
    auto *x = new FileCacheManager("reverse");
    string sol;
    string problem;
    while (getline(cin, problem)) {
        bool c = x->isSolution(problem);
        if (c) {
            sol = x->getSolution(problem);
            std::cout << "exict" << std::endl;
        } else {
            StringRevrser solver;
            sol = solver.solve(problem);
            x->saveSolution(problem, sol);
            std::cout << "new" << std::endl;
        }
        std::cout << sol << std::endl;
    }
    std::cout << "Hello, Hilla - second road good luck to us" << std::endl;
    return 0;
}