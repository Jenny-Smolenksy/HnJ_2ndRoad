//
// Created by jenny on 1/11/19.
//

#ifndef HNJ_2NDROAD_SOLVERSEARCHER_H
#define HNJ_2NDROAD_SOLVERSEARCHER_H

#include <string>
#include "../problem_solve/Solver.h"
#include "ISearchable.h"
#include "ISearcher.h"
#include "Matrix.h"
#include "MatrixSearchProblem.h"
#include "string.h"
template <class Type>
class SolverSearcher : public Solver<MatrixSearchProblem, std::string > {

    ISearcher<int, POINT, string> searcher = new DFS();

    virtual std::string solve(MatrixSearchProblem problem) {
        return searcher.search(problem.getMatrix(), problem.getStartPoint(), problem.getEndPoint());
    }
};


#endif //HNJ_2NDROAD_SOLVERSEARCHER_H
